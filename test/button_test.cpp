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

io::Button test_button1(DISPENSE_BUTTON_PIN);
io::Button test_button2(DOOR_BUTTON_PIN);
bool led_state=false;

void setup(){
    Serial.begin(115200);
    Serial.println("Testing buttons");
    pinMode(13,OUTPUT);
}
void loop(){
        
    test_button1.tick();
    test_button2.tick();

    if (test_button1.getState())
    {
        led_state=!led_state;
        Serial.println("Button 1");
        test_button1.reset();
    }

    if (test_button2.getState())
    {        
        Serial.println("Button 2");
        test_button2.reset();
    }


    if (led_state)
    {
        digitalWrite(13,HIGH);
    }else
    {
        digitalWrite(13,LOW);
    }
            
}