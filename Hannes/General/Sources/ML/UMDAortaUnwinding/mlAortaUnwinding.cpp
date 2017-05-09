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
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();

  // Add fields to the module and set their values.
  m_YSizeFld = addInt("Y-Size", 0);
  m_ZSizeFld = addInt("Z-Size", 0);
  static const char * const MethodValues[] = { "radial","adaptiv" };
  m_MethodFld = addEnum("Method", MethodValues, 1);
  m_MethodFld->setEnumValue(0);
  m_ComputeFld = addNotify("Compute");
  m_Fld = addString("", "");

  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();


  // Activate inplace data buffers for output outputIndex and input inputIndex.
  // setOutputImageInplace(outputIndex, inputIndex);

  // Activate page data bypass from input inputIndex to output outputIndex.
  // Note that the module must still be able to calculate the output image.
  // setBypass(outputIndex, inputIndex);

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

  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).

  // Verify if the input/output data types are supported by our handler.
  // This will invalidate the output image if the type combination is not supported by the handler.
  AortaUnwindingOutputImageHandler::verifyProperties(outputImage);
}

//----------------------------------------------------------------------------------

CalculateOutputImageHandler* AortaUnwinding::createCalculateOutputImageHandler(PagedImage* outputImage)
{
  AortaUnwindingOutputImageHandler::Parameters processingParameters;


  //processingParameters.Y-Size = this->m_YSizeFld->getIntValue();
  //processingParameters.Z-Size = this->m_ZSizeFld->getIntValue();
  //processingParameters.Method = this->m_MethodFld->getEnumValue();
  return new AortaUnwindingOutputImageHandler(outputImage->getOutputIndex(), processingParameters);  
}

ML_END_NAMESPACE