//----------------------------------------------------------------------------------
//! The ML module class AortaUnwinding.
/*!
// \file   
// \author  Hannes
// \date    2017-05-09
//
// 
*/
//----------------------------------------------------------------------------------

#include "mlAortaUnwinding.h"

#include "mlAortaUnwindingOutputImageHandler.h"

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(AortaUnwinding, Module);

//----------------------------------------------------------------------------------

AortaUnwinding::AortaUnwinding() : Module(1, 1)
{

  handleNotificationOff();
  
  // output ImageSize parameters
  m_YSizeFld = addInt("Y-Size", 50);
  m_ZSizeFld = addInt("Z-Size", 80);

  // unwinding method parameter
  static const char * const MethodValues[] = { "radial","adaptiv" };
  m_MethodFld = addEnum("Method", MethodValues, 2);
  m_MethodFld->setEnumValue(0);

  // computation field
  m_ComputeFld = addNotify("Compute");

  // inputs
  m_CenterlineFld = addBase("inCenterline");

  handleNotificationOn();

}

//----------------------------------------------------------------------------------

void AortaUnwinding::handleNotification(Field* field)
{
  // Handle changes of module parameters and input image fields here.
	if (m_ComputeFld == field)
	{
		std::cout << "testcase ready" << std::endl;
	}
}

//----------------------------------------------------------------------------------

void AortaUnwinding::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Setup data types and read-only flags of output image and input sub-images.
  AortaUnwindingOutputImageHandler::setupKnownProperties(outputImage);


  outputImage->setImageExtent(ImageVector(200, m_YSizeFld->getIntValue(), m_ZSizeFld->getIntValue(), 1,1,1));

  AortaUnwindingOutputImageHandler::verifyProperties(outputImage);
}

//----------------------------------------------------------------------------------

CalculateOutputImageHandler* AortaUnwinding::createCalculateOutputImageHandler(PagedImage* outputImage)
{
  AortaUnwindingOutputImageHandler::Parameters processingParameters;

  return new AortaUnwindingOutputImageHandler(outputImage->getOutputIndex(), processingParameters);  
}

ML_END_NAMESPACE