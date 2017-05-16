//----------------------------------------------------------------------------------
//! The ML module output image handle class TestOutputImageHandler.
/*!
// \file    
// \author  Hannes
// \date    2017-05-12
//
// 
*/
//----------------------------------------------------------------------------------

#include "mlTestOutputImageHandler.h"

ML_START_NAMESPACE


TestOutputImageHandler::Parameters::Parameters() 
{

}

TestOutputImageHandler::TestOutputImageHandler(MLint outputIndex, const Parameters& parameters)      
  : _outputIndex( outputIndex )
  , _parameters( parameters )
{
}


template <typename OUTTYPE>
void TestOutputImageHandler::typedCalculateOutputSubImage(TSubImage<OUTTYPE>& outputSubImage,
    UserThreadData* /*userThreadData*/)
{
  // Compute outSubImage.
}

ML_END_NAMESPACE