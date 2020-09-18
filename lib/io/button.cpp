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

// Sets pin for button in INPUT_PULLUP, adds debounce delay time in ms
Button::Button(int pinout,unsigned long debounceDelay){
  pinMode(pinout,INPUT_PULLUP);
  debounceDelay_=debounceDelay;  
}
  
Button::~Button(){

}

// Checks pin state and assures debounce time has passed. Ifnot, returns last
// registered state
int Button::getState(){
  unsigned long timestamp=millis();
  
  if ((timestamp - lastDebounceTime_) > debounceDelay_) {
    lastDebounceTime_=timestamp;
    last_state_!=current_state_;
    current_state_=digitalRead(button_pin_);    
  }else{
    current_state_=last_state_;
  }
  return current_state_;
}

// END OF NAMESPACES -----------------------------------------------------------
}}