//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Hannes
// \date    2017-05-12
*/
//----------------------------------------------------------------------------------


#pragma once


// DLL export macro definition.
#ifdef UMDTEST_EXPORTS
  // Use the UMDTEST_EXPORT macro to export classes and functions.
  #define UMDTEST_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define UMDTEST_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif
