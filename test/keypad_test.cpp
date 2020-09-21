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
#include "../lib/io/keypad.h"
#include "../lib/Keypad_shield/LiquidCrystal.h"


using namespace vibration_dispenser;

io::Keypad interface(KEYPAD_PIN);

LiquidCrystal lcd(pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

void setup(){
  lcd.begin(LCD_COL,LCD_ROW);
  lcd.clear();      
  Serial.begin(115200);
}
void loop(){
    lcd.setCursor(0,0);    
    switch (interface.checkKeys())
    {
    case Key::RIGHT:              
        lcd.print("Right ");
        //delay(200);
        break;
    case Key::UP:              
        lcd.print("Up    ");
        //delay(200);
        break;
    case Key::DOWN:              
        lcd.print("Down  ");
        //delay(200);
        break;
    case Key::LEFT:        
        lcd.print("Left  ");
        //delay(200);
        break;
    case Key::SELECT:        
        lcd.print("Select");
        //delay(200);
        break;
    
    default:
        lcd.print("  ..  ");
        break;
    }    
}
//----------------------END OF UNIT TEST----------------------------------------

