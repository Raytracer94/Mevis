//----------------------------------------------------------------------------------
//! The ML module class AortaUnwinding.
/*!
// \file    
// \author  Hannes
// \date    2017-05-09
//
// 
*/
//----------------------------------------------------------------------------------


#pragma once


#include "UMDAortaUnwindingSystem.h"

#include <mlModuleIncludes.h>

ML_START_NAMESPACE


//! 
class UMDAORTAUNWINDING_EXPORT AortaUnwinding : public Module
{
public:

  //! Constructor.
  AortaUnwinding();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field* field);

  // ----------------------------------------------------------
  //! \name Image processing methods.
  //@{
  // ----------------------------------------------------------

  //! Sets properties of the output image at output \p outputIndex.
  virtual void calculateOutputImageProperties(int outputIndex, PagedImage* outputImage);

  //! Creates the AortaUnwindingHandler for the given output image whenever calculateOutputImageProperties()
  //! is called and the outputImage is valid.
  virtual CalculateOutputImageHandler* createCalculateOutputImageHandler(PagedImage* outputImage);

private:

  // ----------------------------------------------------------
  //! \name Module field declarations
  //@{
  // ----------------------------------------------------------

  //! 
  IntField* m_YSizeFld;
  //! 
  IntField* m_ZSizeFld;
  //! 
  EnumField* m_MethodFld;
  //! 
  NotifyField* m_ComputeFld;
  //! 
  StringField* m_Fld;
  //@}

  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(AortaUnwinding)
};


ML_END_NAMESPACE