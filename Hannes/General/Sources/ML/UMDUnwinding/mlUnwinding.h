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


#pragma once


#include "UMDUnwindingSystem.h"

#include <mlModuleIncludes.h>
#include <mlBase.h>
#include <mlXMarkerList.h>

namespace ml
{
	class cUnwinding;
}

ML_START_NAMESPACE


//! 
class UMDUNWINDING_EXPORT Unwinding : public Module
{
public:

  //! Constructor.
  Unwinding();
  virtual void calculateOutputImageProperties(int _iOutIndex);

  virtual void calculateOutputSubImage(SubImage* outputSubImage, int outputIndex, SubImage* inputSubImages);

  template <typename T>
  void calculateOutputSubImage(TSubImage<T>* outputSubImage, int outputIndex);
  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

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
	std::unique_ptr<cUnwinding> m_pAortaUnwinding;
	std::unique_ptr<cUnwinding> m_ppositionAortaUnwinding;


	// Unwinded Image
	unsigned short* m_psUnwindedImage = NULL;

	XMarkerList* centerline;


	// Variables for realworldcalculation

	XMarkerList m_realworldposition;
	BaseField *m_pOutRealWorldFld;

	Vector3Field* m_unwindedWorldPositionFld;
	Vector3 unwindingPosition;

  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(Unwinding)
};


ML_END_NAMESPACE