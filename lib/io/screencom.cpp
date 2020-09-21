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
  LiquidCrystal lcd(pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
  lcd.begin(LCD_COL,LCD_ROW);
}
Screencom::~Screencom() {

}  
void Screencom::setScreen(Screen menu){

}  
void Screencom::splashScreen(){

}
void Screencom::standbyScreen(){  
  // lcd.clear();
  // lcd.setCursor(0,0);
  // lcd.print("Presione D");
  // lcd.setCursor(0,1);
  // lcd.print("para dispensar");
}
void Screencom::dispensingScreen(){

}
void Screencom::servedScreen(){

}
void Screencom::openDoorScreen(){

}
void Screencom::setWeightScreen(){

}
void Screencom::errorScreen(){

}

// END OF NAMESPACES -----------------------------------------------------------
}}