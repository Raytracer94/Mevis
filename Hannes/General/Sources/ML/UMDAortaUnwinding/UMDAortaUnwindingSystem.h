//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Hannes
// \date    2017-05-09
*/
//----------------------------------------------------------------------------------


#pragma once


// DLL export macro definition.
#ifdef UMDAORTAUNWINDING_EXPORTS
  // Use the UMDAORTAUNWINDING_EXPORT macro to export classes and functions.
  #define UMDAORTAUNWINDING_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define UMDAORTAUNWINDING_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif
