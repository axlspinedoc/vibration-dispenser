//------------------------------------------------------------------------------
// @file: template.cpp
// @created on: May 4, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// INCLUDES --------------------------------------------------------------------
#include "button.h"
// FOWARD DECLARATIONS ---------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace io {  

// ENUMS -----------------------------------------------------------------------

// STRUCTS ---------------------------------------------------------------------

// CLASS IMPLEMENTATION --------------------------------------------------------

Button::Button(){
  
}
  
Button::~Button(){

}

void Button::publicFunction(const long &value) {
  // do something
}
  
int Button::getTemplateValue() const {
  return templateValue_;
}

void Button::setTemplateValue(const int &templateValue) {
  templateValue_ = templateValue;
}
  
void Button::privateFunction() {
  // do something
}

// END OF NAMESPACES -----------------------------------------------------------
}}