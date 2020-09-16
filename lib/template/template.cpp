//------------------------------------------------------------------------------
// @file: template.cpp
// @created on: May 4, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// INCLUDES --------------------------------------------------------------------
#include "template.h"
// FOWARD DECLARATIONS ---------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace xlab { namespace template_ {  

// ENUMS -----------------------------------------------------------------------

// STRUCTS ---------------------------------------------------------------------

// CLASS IMPLEMENTATION --------------------------------------------------------

Template::Template() {
  
}
  
Template::~Template() {

}

void Template::publicFunction(const long &value) {
  // do something
}
  
int Template::getTemplateValue() const {
  return templateValue_;
}

void Template::setTemplateValue(const int &templateValue) {
  templateValue_ = templateValue;
}
  
void Template::privateFunction() {
  // do something
}

// END OF NAMESPACES -----------------------------------------------------------
}}