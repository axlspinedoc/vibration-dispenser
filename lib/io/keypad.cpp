//------------------------------------------------------------------------------
// @file: template.cpp
// @created on: May 4, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// INCLUDES --------------------------------------------------------------------
#include "keypad.h"
// FOWARD DECLARATIONS ---------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace io {  

// CLASS IMPLEMENTATION --------------------------------------------------------

  Keypad::Keypad(int pinout){
  keypad_pin_=pinout;    
  }
  
  Keypad::~Keypad(){
  
  }
  
  Key Keypad::getKey(){
    
    int reading=analogRead(keypad_pin_);
    
    if (reading<RIGHT_VALUE)
    {
        return Key::RIGHT;    
    } 
    else if(reading<UP_VALUE){
        return Key::UP;
    }
    else if(reading<DOWN_VALUE){
        return Key::DOWN;
    }
    else if(reading<LEFT_VALUE){
        return Key::LEFT;
    }
    else if (reading<SELECT_VALUE) {
        return Key::SELECT;
    }
    else
    {
        return Key::NO_KEY;
    }
    
        
  }
  
// END OF NAMESPACES -----------------------------------------------------------
}}