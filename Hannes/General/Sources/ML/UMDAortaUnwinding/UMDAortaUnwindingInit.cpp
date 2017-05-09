//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    
// \author  Hannes
// \date    2017-05-09
*/
//----------------------------------------------------------------------------------

#include "UMDAortaUnwindingSystem.h"

// Include definition of ML_INIT_LIBRARY.
#include <mlLibraryInitMacros.h>

// Include all module headers ...
#include "mlAortaUnwinding.h"


ML_START_NAMESPACE

//----------------------------------------------------------------------------------
//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
//----------------------------------------------------------------------------------
int UMDAortaUnwindingInit()
{
  // Add initClass calls from modules here.
  AortaUnwinding::initClass();

  return 1;
}

ML_END_NAMESPACE


//! Calls the init method implemented above during load of shared library.
ML_INIT_LIBRARY(UMDAortaUnwindingInit)