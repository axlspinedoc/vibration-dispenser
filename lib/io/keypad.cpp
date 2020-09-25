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

  Keypad::Keypad(int pinout, unsigned long debounce_time):
                keypad_pin_(pinout),debounce_time_(debounce_time){
  
  }
  
  Keypad::~Keypad(){
  
  }
  
  Key Keypad::getKey(){

    Key key_state = checkKeys();    
    
    // if (millis()-last_debounce_>debounce_time_)
    // {                    
        if (key_state!=last_key_state_)
        {            
            if (last_key_state_!=Key::NO_KEY)
            {                
                output_key_=last_key_state_;
                last_key_state_=key_state;                        
            } else
            {
                last_key_state_=key_state;            
            }                    
        }
    // }            
    return output_key_;
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

void Keypad::resetKeys(){
    output_key_=Key::NO_KEY;
    last_debounce_=millis();
}
  
// END OF NAMESPACES -----------------------------------------------------------
}}