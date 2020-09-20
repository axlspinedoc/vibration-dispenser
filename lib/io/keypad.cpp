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

  Keypad::Keypad(int pinout,unsigned long debounceDelay){
  keypad_pin_=pinout;
  debounceDelay_=debounceDelay;    
  }
  
  Keypad::~Keypad(){
  
  }
  
  Key Keypad::getKey(){
      
      Key reading = checkKeys();
      if (reading!=last_key_state_){
      lastDebounceTime_ = millis();
    }

    if ((millis() - lastDebounceTime_) > debounceDelay_) {
      if (reading!=key_state_)
      {
        key_state_=reading;        
        if (key_state_!=Key::NO_KEY)
        {
          output_key_ = reading;
        }
      }
              
    }    
    last_key_state_=reading;    
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

  
// END OF NAMESPACES -----------------------------------------------------------
}}