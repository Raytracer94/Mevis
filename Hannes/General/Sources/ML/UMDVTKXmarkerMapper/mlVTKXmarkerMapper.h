//----------------------------------------------------------------------------------
//! The ML module class VTKXmarkerMapper.
/*!
// \file    
// \author  Hannes
// \date    2017-06-21
//
// 
*/
//----------------------------------------------------------------------------------


#pragma once


#include "UMDVTKXmarkerMapperSystem.h"

#include <mlModuleIncludes.h>
#include <mlBase.h>
#include <mlXMarkerList.h>
ML_START_NAMESPACE


//! 
class UMDVTKXMARKERMAPPER_EXPORT VTKXmarkerMapper : public Module
{
public:

  //! Constructor.
  VTKXmarkerMapper();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);
  // input
  BaseField* m_VtkCenterlineFld;
  NotifyField* m_updateFld;


  // output

  BaseField* m_outAorticCenterlineMarkerFld;
  XMarkerList m_AorticCenterlineMarker;
private:



  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(VTKXmarkerMapper)
};


ML_END_NAMESPACE