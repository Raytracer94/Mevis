//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Hannes
// \date    2017-06-20
*/
//----------------------------------------------------------------------------------

#include "UMDUnwindingSystem.h"

// Include definition of ML_INIT_LIBRARY.
#include <mlLibraryInitMacros.h>

// Include all module headers ...
#include "mlUnwinding.h"
#include "cUnwinding.h"

ML_START_NAMESPACE

//----------------------------------------------------------------------------------
//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
//----------------------------------------------------------------------------------
int UMDUnwindingInit()
{
  // Add initClass calls from modules here.
  Unwinding::initClass();

  return 1;
}

ML_END_NAMESPACE


//! Calls the init method implemented above during load of shared library.
ML_INIT_LIBRARY(UMDUnwindingInit)