#pragma once
#include "UMDTestSystem.h"
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyData.h>
#include <mlModuleIncludes.h>
#include <mlPagedImage.h>
#include <math.h>
#include <mlBase.h>
#include <mlXMarkerList.h>
#include <mlRotation.h>
ML_START_NAMESPACE

class  Unwinding
{
public:
	// constructor definition 

	Unwinding(PagedImage* inputImage, XMarkerList* pXmarkerList,MLint XSize, MLint YSize,MLint ZSize,unsigned short* m_psUnwindedImage);
	
	~Unwinding();
	// unwinding methods
	int calculateUnwindedImageViaCircles();
	int calculateUnwindedImageViaAdaptiv();
	
	// recalculation method
	int calculateRealAortaPosition(XMarkerList realworldposition,Vector3 UnwindingPosition,int sampletype);


	// constructor variables

	unsigned short* UnwindedImage;
	PagedImage* inImage;
	MLint xSize;
	MLint ySize;
	MLint zSize;
	XMarkerList* centerline;

	// sub image to get datavalues
	const SubImageBox UnwindedImageBox;
	const SubImage UnwindedSubImage;

	// methods

	unsigned short getGreyValue(Vector3 position);
	unsigned short linearInterpolation(Vector3 position);
};
ML_END_NAMESPACE
