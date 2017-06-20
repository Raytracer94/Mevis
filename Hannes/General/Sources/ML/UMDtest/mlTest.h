//----------------------------------------------------------------------------------
//! The ML module class Test.
/*!
// \file    
// \author  Hannes
// \date    2017-05-12
//
// 
*/
//----------------------------------------------------------------------------------


#pragma once

// Local includes
#include "mlVTKCommonWrappers.h"
#include <vtkParametricFunction.h>
#include <vtkSmartPointer.h>

#include "UMDTestSystem.h"
#include <mlModuleIncludes.h>
#include <mlBase.h>
#include <mlXMarkerList.h>
#include <math.h>

namespace ml
{
	class Unwinding;
}

ML_START_NAMESPACE


//! 
class UMDTEST_EXPORT Test : public Module
{
public:

  Test();
  virtual void handleNotification (Field* field);
  virtual void calculateOutputImageProperties(int _iOutIndex);

  virtual void calculateOutputSubImage(SubImage* outputSubImage, int outputIndex, SubImage* inputSubImages);

  template <typename T>
  void calculateOutputSubImage (TSubImage<T>* outputSubImage, int outputIndex);
  //@}

private:

	// user inputs
	IntField* m_YSizeFld;
	IntField* m_ZSizeFld;
	EnumField* m_MethodFld;

	// Buttons
	NotifyField* m_ComputeFld;
	NotifyField* m_RealPosFld;
	// centerline
	BaseField* m_CenterlineFld;

	//centerline 
	// outputimage sizes
	MLint m_uiUnwindedImageWidth;
	MLint m_uiUnwindedImageHeight;
	MLint m_uiUnwindedImageDepth;

	// pointer for Unwinded image calculation
	std::unique_ptr<Unwinding> m_pAortaUnwinding;
	std::unique_ptr<Unwinding> m_ppositionAortaUnwinding; 
	
	
	// Unwinded Image
	unsigned short* m_psUnwindedImage = NULL;


	// Variables for realworldcalculation
	
	XMarkerList m_realworldposition;
	BaseField *m_pOutRealWorldFld;

	Vector3Field* m_unwindedWorldPositionFld;
	Vector3 unwindingPosition;

  ML_MODULE_CLASS_HEADER(Test)
};


ML_END_NAMESPACE