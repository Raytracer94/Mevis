//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Hannes
// \date    2017-06-20
*/
//----------------------------------------------------------------------------------


#pragma once


// DLL export macro definition.
#ifdef UMDUNWINDING_EXPORTS
  // Use the UMDUNWINDING_EXPORT macro to export classes and functions.
  #define UMDUNWINDING_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define UMDUNWINDING_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif
