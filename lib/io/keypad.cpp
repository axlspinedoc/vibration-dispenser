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

  Keypad::Keypad(int pinout):
                keypad_pin_(pinout){
  
  }
  
  Keypad::~Keypad(){
  
  }
  
  Key Keypad::getKey(){

    Key key_state = checkKeys();            
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
    return output_key_;
}

// Utiliza valores a partir de 0.01 hasta 0.95
//
// AJUSTA AQUÍ LA SENSIBILIDAD DE LOS BOTONES PARA LAS FLECHAS -----¬
//                                                                  |
Key Keypad::checkKeys(){                                        //  |
    int reading=analogRead(keypad_pin_);                        //  |
    //                                                              |
    //                                                              |
    //                                                              v                                                                    
    if (reading<RIGHT_VALUE && reading>(int)(RIGHT_VALUE*           0.8))
    {
        return Key::RIGHT;    
    } 
    else if(reading<UP_VALUE && reading>(int)(UP_VALUE*             0.8)){
        return Key::UP;
    }
    else if(reading<DOWN_VALUE && reading>(int)(DOWN_VALUE*         0.8)){
        return Key::DOWN;
    }
    else if(reading<LEFT_VALUE && reading>(int)(LEFT_VALUE*         0.8)){
        return Key::LEFT;
    }
    else if (reading<SELECT_VALUE && reading>(int)(SELECT_VALUE*    0.8)) {
        return Key::SELECT;
    }
    else{
        return Key::NO_KEY;
    }    
}

void Keypad::resetKeys(){
    output_key_=Key::NO_KEY;
    // Added to avoid bouncing, root cause is wrong hardware modification
    delay(PAUSA_FLECHAS);    
}
  
// END OF NAMESPACES -----------------------------------------------------------
}}