#include "Unwinding.h"

ML_START_NAMESPACE


Unwinding::Unwinding(PagedImage * inputImage, XMarkerList* pXmarkerList, MLint XSize, MLint YSize, MLint ZSize, unsigned short * m_psUnwindedImage)
{
	inImage = inputImage;
	xSize = XSize;
	ySize = YSize;
	zSize = ZSize;
	UnwindedImage = m_psUnwindedImage;
	centerline = pXmarkerList;

	const SubImageBox UnwindedImageBox(ImageVector(0, 0, 0, 0, 0, 0), ImageVector(xSize - 1,ySize - 1, zSize - 1, 0, 0, 0));

	const SubImage UnwindedSubImage(UnwindedImageBox, MLuint16Type, (void*)UnwindedImage);

}

Unwinding::~Unwinding()
{
}

//----------------------------------------------------------------------------------
// Unwind the aorta via radial approach
//----------------------------------------------------------------------------------
int Unwinding::calculateUnwindedImageViaCircles()
{
	// parameter for sampling 

	// rotation variables
	Vector3 axis;
	XMarker currpointmarker;
	Vector3 currpoint;
	XMarker nextpointmarker;
	Vector3 nextpoint;
	Vector3 upvector;
	// initial sample point 
	Vector3 sampledpoint;

	// y variables
	double currdegree= 0;
	double degreestep = zSize / 360;

	// z variables
	double zstep = 0;
	double zsamplingstep = ySize / 36;

	// sampling step
	for (int x = 0; x < centerline->getSize(); x++)  // centerline
	{
		if (x < centerline->getSize() - 1)
		{
			currpointmarker = centerline->at(x);
			currpoint = Vector3(currpointmarker.x(), currpointmarker.y(), currpointmarker.z());
			nextpointmarker = centerline->at(x + 1);
			nextpoint = Vector3(nextpointmarker.x(), nextpointmarker.y(), nextpointmarker.z());

			axis = nextpoint - currpoint;
		}
		else
		{
			currpointmarker = centerline->at(x - 1);
			currpoint = Vector3(currpointmarker.x(), currpointmarker.y(), currpointmarker.z());
			nextpointmarker = centerline->at(x - 1);
			nextpoint = Vector3(nextpointmarker.x(), nextpointmarker.y(), nextpointmarker.z());
			axis = currpoint - nextpoint;
		}
		for (int y = 0; y < ySize; y++) // angle 
		{
			for (int z = 0; z < zSize; z++) // depthstep
			{
				upvector = currpointmarker.vec;
				sampledpoint =  currpoint + upvector*zstep;//  * ml::rotation3D(axis, (currdegree*ML_M_PI) / 180);
				UnwindedImage[z*ySize*zSize + y*zSize + x] = linearInterpolation(sampledpoint);
				zstep += zsamplingstep;
			}
			currdegree += degreestep;
		}
	}
	
	return 0;
}
//----------------------------------------------------------------------------------
// Unwind the aorta via adaptiv method
//----------------------------------------------------------------------------------
int Unwinding::calculateUnwindedImageViaAdaptiv()
{
	// parameter for sampling 

	// rotation variables
	Vector3 axis;
	XMarker currpointmarker;
	Vector3 currpoint;
	XMarker nextpointmarker;
	Vector3 nextpoint;
	Vector3 upvector;

	// initial sample point 
	Vector3 sampledpoint;

	// y variables
	double currdegree = 0;
	double degreestep = zSize / 360;

	// z variables
	double zstep = 0;

	double zsamplingstep; // dynamically calculation per raylength
	double raylength;

	// sampling step
	for (int x = 0; x < centerline->getSize(); x++)  // centerline
	{
		currdegree = 0; // set currdegree 0 for next centerline point
		if (x < centerline->getSize() - 1)
		{
			currpointmarker = centerline->at(x);
			currpoint = Vector3(currpointmarker.x(), currpointmarker.y(), currpointmarker.z());
			nextpointmarker = centerline->at(x + 1);
			nextpoint = Vector3(nextpointmarker.x(), nextpointmarker.y(), nextpointmarker.z());

			axis = nextpoint - currpoint;
		}
		else
		{
			currpointmarker = centerline->at(x - 1);
			currpoint = Vector3(currpointmarker.x(), currpointmarker.y(), currpointmarker.z());
			nextpointmarker = centerline->at(x-1);
			nextpoint = Vector3(nextpointmarker.x(), nextpointmarker.y(), nextpointmarker.z());
			axis = currpoint - nextpoint;
		}
		for (int y = 0; y < ySize; y++) // angle 
		{
			zstep = 0;// set zstep  0 for next angle 

			// adaptiv tracing of the  raylength for each angle 
			for (int currraylength; currraylength < 40; currraylength++)
			{
				sampledpoint = currpoint + upvector*currraylength;//  *ml::rotation3D(axis, (currdegree*ML_M_PI) / 180);
				if (getGreyValue(sampledpoint) == 0)
				{
					currraylength++;
					raylength = currraylength;
					break;
				}
				raylength = currraylength;
			}

			for (int z = 0; z < zSize; z++) // depthstep
			{
				zsamplingstep = raylength / zSize;
				upvector = currpointmarker.vec;
				sampledpoint = currpoint + upvector*zstep;//  * ml::rotation3D(axis, (currdegree*ML_M_PI) / 180);
				UnwindedImage[z*ySize*zSize + y*zSize + x] = linearInterpolation(sampledpoint);
				zstep += zsamplingstep;
			}
			currdegree += degreestep;
		}
	}
	return 0;
}

//----------------------------------------------------------------------------------
// Compute the OriginalPosition
//----------------------------------------------------------------------------------
int Unwinding::calculateRealAortaPosition(XMarkerList realworldposition, Vector3 UnwindingPosition, int sampletype)
{
	if (sampletype == 0) // realworld calculation for radial approach 
	{
		XMarker nextmarker;
		Vector3 nextpoint;
		Vector3 axis;
		// get corresponding xmarker in centerline 
		XMarker currpointmarker = centerline->at(UnwindingPosition.x);
		Vector3 currpoint = Vector3(currpointmarker.x(), currpointmarker.y(), currpointmarker.z());

		// get next xmarker in centerline for axis 
		if(currpoint.x < centerline->getSize()-1)
		{
			nextmarker = centerline->at(UnwindingPosition.x + 1);
			nextpoint = Vector3(nextmarker.x(), nextmarker.y(), nextmarker.z());

			axis = nextpoint - currpoint;
		}
		else // here the nextpoint is the previous point
		{
			nextmarker = centerline->at(UnwindingPosition.x -1);
			nextpoint = Vector3(nextmarker.x(), nextmarker.y(), nextmarker.z());

			axis = currpoint - nextpoint;
		}

		// find correct y-Position by getting y-coord 

		double yratio = UnwindingPosition.y / ySize;

		yratio = 360 * yratio;
		// find correct depth of the position
		double zratio = UnwindingPosition.z / zSize;
		
		// upvector transformation to the point 
		Vector3 upvector = currpointmarker.vec;
		Vector3 realposition = currpoint + upvector*zratio;//* ml::rotation3D(axis, (yratio*ML_M_PI) / 180);

		realworldposition.push_back(realposition);
	}
	else if (sampletype == 1)// realworld calculation for adaptiv approach
	{
		XMarker nextmarker;
		Vector3 nextpoint;
		Vector3 axis;
		// get corresponding xmarker in centerline 
		XMarker currpointmarker = centerline->at(UnwindingPosition.x);
		Vector3 currpoint = Vector3(currpointmarker.x(), currpointmarker.y(), currpointmarker.z());

		// get next xmarker in centerline for axis 
		if (currpoint.x < centerline->getSize() - 1)
		{
			nextmarker = centerline->at(UnwindingPosition.x + 1);
			nextpoint = Vector3(nextmarker.x(), nextmarker.y(), nextmarker.z());

			axis = nextpoint - currpoint;
		}
		else // here the nextpoint is the previous point
		{
			nextmarker = centerline->at(UnwindingPosition.x - 1);
			nextpoint = Vector3(nextmarker.x(), nextmarker.y(), nextmarker.z());

			axis = currpoint - nextpoint;
		}

		// find correct y-Position by getting y-coord 

		double yratio = UnwindingPosition.y / ySize;

		yratio = 360 * yratio;
		// find correct depth of the position

		// first step detect raylength on the angle
		Vector3 samplepoint;
		Vector3 upvector = currpointmarker.vec;
		double raylength;
		for (int currraylength; currraylength < 40; currraylength++)
		{
			samplepoint = currpoint + upvector*currraylength;//  * ml::rotation3D(axis, (yratio*ML_M_PI) / 180);
			if (getGreyValue(samplepoint) == 0)
			{
				currraylength++;
				raylength = currraylength;
				break;
			}
			raylength = currraylength;
		}

		double zratio = UnwindingPosition.z /raylength;

		// upvector transformation to the point
		Vector3 realposition = currpoint + upvector*zratio;//  * ml::rotation3D(axis, (yratio*ML_M_PI) / 180);

		realworldposition.push_back(realposition);
	}
	return 0;
}
//----------------------------------------------------------------------------------
// linear Interpolation of the grey values
//----------------------------------------------------------------------------------
unsigned short Unwinding::linearInterpolation(Vector3 position)
{
	// weights for interpolation

	double xWeight = (position.x - (position.x - 1)) / ((position.x + 1) - (position.x - 1));
	double yWeight = (position.y - (position.y - 1)) / ((position.y + 1) - (position.y - 1));
	double zWeight = (position.z - (position.z - 1)) / ((position.z + 1) - (position.z - 1));
		
	// 8 neighbours to position
	unsigned short greyvalue1 = getGreyValue(position);
	unsigned short greyvalue2 = getGreyValue(Vector3(position.x+1,position.y,position.z));
	unsigned short greyvalue3 = getGreyValue(Vector3(position.x, position.y+1, position.z));
	unsigned short greyvalue4 = getGreyValue(Vector3(position.x+1, position.y+1, position.z));
	unsigned short greyvalue5 = getGreyValue(Vector3(position.x, position.y, position.z+1));
	unsigned short greyvalue6 = getGreyValue(Vector3(position.x+1, position.y, position.z+1));
	unsigned short greyvalue7 = getGreyValue(Vector3(position.x, position.y+1, position.z+1));
	unsigned short greyvalue8 = getGreyValue(Vector3(position.x+1, position.y+1, position.z+1));

	// interpolate in x-direction

	double c00 = greyvalue1*(1 - xWeight) + greyvalue2*xWeight;
	double c01 = greyvalue3*(1 - xWeight) + greyvalue4*xWeight;
	double c10 = greyvalue5*(1 - xWeight) + greyvalue6*xWeight;
	double c11 = greyvalue7*(1 - xWeight) + greyvalue8*xWeight;

	// interpolate in y-direction

	double c0 = c00*(1 - yWeight) + c01*yWeight;
	double c1 = c10*(1 - yWeight) + c11*yWeight;

	// interpolate in z-direction

	unsigned short c = static_cast<unsigned short>(c0*(1 - zWeight) + c1*zWeight);
	return c;
}
//----------------------------------------------------------------------------------
// Get the grey value in the original image
//----------------------------------------------------------------------------------
unsigned short Unwinding::getGreyValue(Vector3 position)
{
	unsigned short* greyvalue =  static_cast<unsigned short*>(UnwindedSubImage.getImagePointer(ImageVector((MLint)position.x, (MLint)position.y, (MLint)position.z, 0, 0, 0)));
	return *greyvalue;
}
ML_END_NAMESPACE