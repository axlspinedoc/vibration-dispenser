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

    Key key_state = checkKeys();
    Key output_key;
    if (key_state!=last_key_state_)
    {
        if (key_state==Key::NO_KEY)
        {
            output_key=last_key_state_;
            key_state=last_key_state_;
        } else
        {
            last_key_state_=key_state;
            output_key=Key::NO_KEY;
        }
        output_key=Key::NO_KEY;                
    }
            
    return output_key;
}

Key Keypad::checkKeys(){
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
    else{
        return Key::NO_KEY;
    }    
}

  
// END OF NAMESPACES -----------------------------------------------------------
}}