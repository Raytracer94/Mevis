//----------------------------------------------------------------------------------
//! The ML module output image handle class AortaUnwindingOutputImageHandler.
/*!
// \file    
// \author  Hannes
// \date    2017-05-09
//
// 
*/
//----------------------------------------------------------------------------------

#pragma once

#include <mlTypedHandlers.h>

ML_START_NAMESPACE

//! The AortaUnwindingOutputImageHandler handles the page calculation of an output image of AortaUnwinding.
//! It should receive all required state from its caller in its
//! constructor and should not keep a reference to the output image nor the module itself.
//! This facilitates to implement a thread safe handler, which does not access non-thread safe shared data,
//! and which can be easily reused by other modules or within other contexts.
class AortaUnwindingOutputImageHandler : public TypedCalculateOutputImageHandler<AortaUnwindingOutputImageHandler,
    /* numInputs = */ 1,
    /* MLVariableType0 = */ ScalarTypes>
{

public:
  //! Struct for processing parameters
  struct Parameters 
  {

    MLint YSize; //!< 
    MLint ZSize; //!< 
    int Method; //!< 
  
    //! Default constructor ensuring that all variables are initialized.
    Parameters();
  };
  
  //! Template configuration of the output/input sub-images.
  enum {
    OutputSubImage_Type = MLVariableType0,
    InputSubImage0_Type = MLVariableType0,
    InputSubImage0_ReadOnly = true
  };

private:
  //! Output index: Range depends on the number of output images/modes. 
  //! The first output image/mode has index 0.
  MLint _outputIndex;  
  
  //! Processing parameter set
  Parameters _parameters;

public:
  //----------------------------------------------------------------------------------
  //! Construct a new handler for given \p outputImage and given module state.
  //! Do not keep references to the outputImage or the module, the needed state
  //! is copied instead.
  //----------------------------------------------------------------------------------
  AortaUnwindingOutputImageHandler(MLint outputIndex, const Parameters& parameters);
  
  //----------------------------------------------------------------------------------
  //! Returns the input image region required to calculate a region of an output image.
  //----------------------------------------------------------------------------------
  SubImageBox calculateInputSubImageBox(int inputIndex, const SubImageBox& outputSubImageBox);

  //----------------------------------------------------------------------------------
  //! Templated output page calculation: compute output sub-image from input sub-image(s)
  //----------------------------------------------------------------------------------
template <typename OUTTYPE>
void typedCalculateOutputSubImage(TSubImage<OUTTYPE>& outputSubImage,
    const TSubImage<OUTTYPE>& inputSubImage0,
    UserThreadData* /*userThreadData*/);
};

ML_END_NAMESPACE