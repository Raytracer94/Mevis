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

#include "mlVTKXmarkerMapper.h"


ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(VTKXmarkerMapper, Module);

//----------------------------------------------------------------------------------

VTKXmarkerMapper::VTKXmarkerMapper() : Module(0, 0)
{
	ML_TRACE_IN("VTKXmarkerMapper::VTKXmarkerMapper()");
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();

  //in Field
  m_VtkCenterlineFld = addBase("InAortaVTK");
  m_updateFld = addNotify("StartMapper");
  //outField

  m_outAorticCenterlineMarkerFld = addBase("outAorticMarker", &m_AorticCenterlineMarker);

  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();

}

//----------------------------------------------------------------------------------

void VTKXmarkerMapper::handleNotification(Field* field)
{
	if (m_updateFld == field)
	{
		std::cout << "Klasse" << std:: endl;
	}
  // Handle changes of module parameters and input image fields here.
}

ML_END_NAMESPACE