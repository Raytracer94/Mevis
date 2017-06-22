//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  Hannes
// \date    2017-06-21
*/
//----------------------------------------------------------------------------------


#pragma once


// DLL export macro definition.
#ifdef UMDVTKXMARKERMAPPER_EXPORTS
  // Use the UMDVTKXMARKERMAPPER_EXPORT macro to export classes and functions.
  #define UMDVTKXMARKERMAPPER_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define UMDVTKXMARKERMAPPER_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif
