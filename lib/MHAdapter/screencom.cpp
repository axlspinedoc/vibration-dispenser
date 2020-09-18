//------------------------------------------------------------------------------
// @file: template.cpp
// @created on: May 4, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// INCLUDES --------------------------------------------------------------------
#include "screencom.h"
// FOWARD DECLARATIONS ---------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace io {  

// ENUMS -----------------------------------------------------------------------

// STRUCTS ---------------------------------------------------------------------

// CLASS IMPLEMENTATION --------------------------------------------------------

Screencom::Screencom() {
  lcd.begin();
  lcd.clear();  
  lcd.setCursor(1,1);
  lcd.print("System initialized");
  lcd.setCursor(1,3);
  lcd.print("V0.1");  
}
  
Screencom::~Screencom() {

}

void Screencom::publicFunction(const long &value) {
  // do something
}

// END OF NAMESPACES -----------------------------------------------------------
}}