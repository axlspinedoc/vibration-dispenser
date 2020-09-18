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
  button_pin_=pinout;
  pinMode(pinout,INPUT_PULLUP);
  debounceDelay_=debounceDelay;  
}
  
Button::~Button(){

}

// Constantly checks for a state change in the pin. After completing debounce
// time, output state changes to true. Output state must be reset after read.
void Button::tick(){
  
    int reading=digitalRead(button_pin_);
    if (reading!=last_button_state_)
      lastDebounceTime_=millis();


    if ((millis() - lastDebounceTime_) > debounceDelay_) {
      if (reading!=button_state_)
      {
        button_state_=reading;
        output_state_=true;
      }
        
    }
    
    last_button_state_=reading;
}

// Checks pin state and assures debounce time has passed. Ifnot, returns last
// registered state
int Button::getState(){
  return output_state_;
}

void Button::reset(){
  output_state_=LOW;
}

// END OF NAMESPACES -----------------------------------------------------------
}}