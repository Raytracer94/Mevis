//----------------------------------------------------------------------------------
//! The ML module class Unwinding.
/*!
// \file   
// \author  Hannes
// \date    2017-06-20
//
// 
*/
//----------------------------------------------------------------------------------

#include "mlUnwinding.h"
#include "cUnwinding.h"
#include <algorithm>

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(Unwinding, Module);

//----------------------------------------------------------------------------------

Unwinding::Unwinding() : Module(2, 1)
{
	ML_TRACE_IN("Unwinding::Unwinding()");
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();
  // output ImageSize parameters
  m_YSizeFld = addInt("Y-Size", 50);
  m_ZSizeFld = addInt("Z-Size", 80);

  // unwinding method parameter
  static const char * const MethodValues[] = { "radial","adaptiv" };
  m_MethodFld = addEnum("Method", MethodValues, 1);
  m_MethodFld->setEnumValue(0);

  // computation field
  m_ComputeFld = addNotify("Compute");
  // inputs
  m_CenterlineFld = addBase("inCenterline");


  //inputs and outputs for realworldcalculation

  m_RealPosFld = addNotify("Compute RealPosition");
  m_unwindedWorldPositionFld = addVector3("unwindedPosition");
  m_pOutRealWorldFld = addBase("outrealposition", &m_realworldposition);
  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();

}

//----------------------------------------------------------------------------------

void Unwinding::handleNotification(Field* field)
{
	ML_TRACE_IN("Unwinding::handleNotification()");
	if (m_ComputeFld == field)
	{

		// get centerline 
		XMarkerList* pXmarkerList = mlbase_cast<XMarkerList*>(m_CenterlineFld->getBaseValue());
		// set imagesizes

		m_uiUnwindedImageWidth = static_cast<MLint>(pXmarkerList->getSize());
		m_uiUnwindedImageHeight = m_YSizeFld->getIntValue();
		m_uiUnwindedImageDepth = m_ZSizeFld->getIntValue();

		// automatically deletes old memory
		if (m_psUnwindedImage) {
			delete(m_psUnwindedImage);
		}
		m_psUnwindedImage = new unsigned short[m_uiUnwindedImageWidth*m_uiUnwindedImageHeight*m_uiUnwindedImageDepth];

		// test for valid input datas
		if (getUpdatedInputImage(0))
		{
			m_pAortaUnwinding = std::unique_ptr<cUnwinding>(new cUnwinding(getUpdatedInputImage(0), pXmarkerList, m_uiUnwindedImageWidth, m_uiUnwindedImageHeight, m_uiUnwindedImageDepth, m_psUnwindedImage));

			// calculates the unwinded image by chosen method
			if (m_MethodFld->getEnumValue() == 0)
			{
				std::cout << "start radial" << std::endl;
				m_pAortaUnwinding->calculateUnwindedImageViaCircles();
			}
			else if (m_MethodFld->getEnumValue() == 1)
			{
				std::cout << "start adaptiv" << std::endl;
				m_pAortaUnwinding->calculateUnwindedImageViaAdaptiv();
			}
			else
			{
				std::cout << "No correct Unwinding Method chosen" << std::endl;
			}
		}
		else
		{
			std::cout << "No valid image or centerline" << std::endl;
		}

	}

	if (m_RealPosFld == field)
	{
		std::cout << "start Positioncalculation" << std::endl;
		if (m_pAortaUnwinding)
		{
			// get Sampletype 

			int sampletype = m_MethodFld->getEnumValue();

			m_realworldposition.clear();
			auto pXmarkerList = mlbase_cast<XMarkerList*>(m_CenterlineFld->getBaseValue());
			m_ppositionAortaUnwinding = std::unique_ptr<cUnwinding>(new cUnwinding(getUpdatedInputImage(1), pXmarkerList, m_uiUnwindedImageWidth, m_uiUnwindedImageHeight, m_uiUnwindedImageDepth, m_psUnwindedImage));

			unwindingPosition = m_unwindedWorldPositionFld->getVector3Value();
			m_ppositionAortaUnwinding->calculateRealAortaPosition(m_realworldposition, unwindingPosition, sampletype);

			m_pOutRealWorldFld->touch();
		}
		else
		{
			std::cout << "No AortaUnwinding exist" << std::endl;
		}
	}
  // Handle changes of module parameters and input image fields here.
}
//----------------------------------------------------------------------------------

void Unwinding::calculateOutputImageProperties(int _iOutputIndex)
{
	ML_TRACE_IN("Unwinding::calculateOutputImageProperties()");

	PagedImage* pOutputImage = getOutputImage(_iOutputIndex);


	// create container image			
	pOutputImage->setImageExtent(ImageVector(m_uiUnwindedImageWidth, m_uiUnwindedImageHeight, m_uiUnwindedImageDepth, 1, 1, 1));
	pOutputImage->setPageExtent(ImageVector(m_uiUnwindedImageWidth, m_uiUnwindedImageHeight, m_uiUnwindedImageDepth, 1, 1, 1));

	pOutputImage->setMinVoxelValue(getUpdatedInputImage(0)->getMinVoxelValue());

	pOutputImage->setMaxVoxelValue(getUpdatedInputImage(0)->getMaxVoxelValue());
	pOutputImage->setVoxelSize(getUpdatedInputImage(0)->getVoxelSize());
	pOutputImage->setDataType(getUpdatedInputImage(0)->getDataType());
	pOutputImage->setValid();
}

//----------------------------------------------------------------------------------
ML_CALCULATEOUTPUTSUBIMAGE_NUM_INPUTS_0_SCALAR_TYPES_CPP(Unwinding);

template <typename T>
void Unwinding::calculateOutputSubImage(TSubImage<T>* outputSubImage, int outputIndex)
{

	ML_TRACE_IN("template<typename T> Unwinding::calculateOutputSubImage()");


	if (outputIndex == 0)
	{
		const SubImageBox UnwindedImageBox(ImageVector(0, 0, 0, 0, 0, 0), ImageVector(m_uiUnwindedImageWidth - 1,
			m_uiUnwindedImageHeight - 1, m_uiUnwindedImageDepth - 1, 0, 0, 0));

		const TSubImage<T> UnwindedSubImage(UnwindedImageBox, MLuint16Type, (void*)m_psUnwindedImage);
		//const SubImage UnwindedSubImage(UnwindedImageBox, MLuint16Type, (void*)m_psUnwindedImage);
		outputSubImage->copySubImage(UnwindedSubImage);
	}

}
ML_END_NAMESPACE