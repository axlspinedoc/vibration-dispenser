

//------------------------------------------------------------------------------
// @file: button_test.cpp
// @author: Axel Sandoval
// @e-mail: axel_isc@hotmail.com
// @created on: September 15, 2020
// 
//
// @brief: Test code for Button library
// LICENCE
//------------------------------------------------------------------------------

#include <Arduino.h>
#include "../lib/inc/utilites.h"
#include "../lib/io/button.h"

using namespace vibration_dispenser;

io::Button test_button(DISPENSE_BUTTON_PIN);
bool led_state=false;

void setup(){
    Serial.begin(115200);
}
void loop(){
        
    //test_button.tick();

    if (test_button.getState())
    {
        led_state=!led_state;
        Serial.println("Pushed");        
        test_button.reset();
    }

    // if (led_state)
    // {
    //     Serial.println("Pushed");
    // }else
    // {
    //     Serial.println("Off");
    // }
            
}