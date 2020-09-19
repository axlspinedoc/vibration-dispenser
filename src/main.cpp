//------------------------------------------------------------------------------
// @file: main.cpp
// @author: Axel Sandoval
// @e-mail: axel_isc@hotmail.com
// @created on: September 15, 2020
// 
//
// @brief: Source code for a vibration dispenser machine with scalability.
// LICENCE
//------------------------------------------------------------------------------

#include <Arduino.h>
#include <Servo.h>
#include "../lib/inc/utilites.h"
#include "../lib/state_machine/state_machine.h"
#include "../lib/MHAdapter/LiquidCrystal_I2C.h"
#include "../lib/io/button.h"
#include "../lib/io/keypad.h"
#include "../lib/io/screencom.h"

using namespace vibration_dispenser;

control::State_machine machine_state;
// io::Button door_button(DOOR_BUTTON);
// io::Button disp_button(DISPENSE_BUTTON);
// io::Keypad keypad(KEYPAD_PIN);
// io::Screencom screen();


Servo door_servo;

// Screencom
LiquidCrystal lcd(pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

// Serial comm DEBUGGING
char incomingChar;
int weight=0;
bool weight_changed=false;

void setup() {
  
  Serial.begin(115200);
  Serial.println("System initialized");
  door_servo.attach(SERVO_PIN);
  door_servo.write(DOOR_CLOSED);
  
  lcd.begin(LCD_COL,LCD_ROW);
  lcd.clear();    
  lcd.setCursor(0,0);  
  lcd.print("Sistema iniciado");
  lcd.setCursor(0,1);
  lcd.print("V0.1");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Presione D");
  lcd.setCursor(0,1);
  lcd.print("para dispensar");
  // lcd.setCursor(0,2);      
  // lcd.print("Presione W para");
  // lcd.setCursor(0,3);
  // lcd.print("cambiar gramaje");
}

// Forward declarations

// Checks status of functions inside on each loop
void tick();

void loop() {
  
  if (Serial.available()>0)
  {
    if (Serial.available()==1)
    {
      // Single key: Next Stage
      incomingChar=Serial.read();
    }else{
      // Char chain: Set Weight
      
      int bytesAvailable=Serial.available();          
      String serialBuffer="";

      for (int idx = 0; idx<bytesAvailable;  idx++) {            
        char input_char = Serial.read();            
        serialBuffer = serialBuffer + input_char;            
        }
      weight=serialBuffer.toInt();
      weight_changed=true;
      
    }
    
  }
  
    switch (machine_state.getState())
    {
    case control::State::STANDBY:
      

      if (incomingChar=='W')
      {
        machine_state.setState(control::State::SETGRAMS);
        Serial.println("State:= SETGRAMS");
        
      } else if(incomingChar=='D'){

        machine_state.setState(control::State::DISPENSING);
        Serial.println("State:= DISPENSING");
        
        lcd.clear();
        lcd.print("Dispensando...");      
        lcd.setCursor(0,1);      
        lcd.print("S para detener");
      }     
      break;
    
    case control::State::SETGRAMS:
      
      if (weight_changed)
      {
        Serial.print("Weight set to= ");
        Serial.println(weight);
        weight_changed=false;
      }    
      
      if (incomingChar=='Q')
      {        
        machine_state.setState(control::State::STANDBY);
        Serial.println("State:= STANDBY");
      }
      break;

    case control::State::DISPENSING:
      
      
      if (incomingChar=='S')
      {        
        machine_state.setState(control::State::SERVED);
        Serial.println("State:= SERVED");
        lcd.clear();
        lcd.print("Presione F para");   
        lcd.setCursor(0,1);
        lcd.print("vaciar tolva");
      }
      break;  

    case control::State::SERVED:
               
      if (incomingChar=='F')
      {        
        machine_state.setState(control::State::FLUSH);
        Serial.println("State:= FLUSH");
        door_servo.write(DOOR_OPEN);      
        lcd.clear();
        lcd.print("Presione R para"); 
        lcd.setCursor(0,1);
        lcd.print("terminar vaciado"); 
      }
      break;

    case control::State::FLUSH:      
      
      if (incomingChar=='R')
      {        
        machine_state.setState(control::State::STANDBY);
        Serial.println("State:= STANDBY");
        door_servo.write(DOOR_CLOSED);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Presione D");
        lcd.setCursor(0,1);
        lcd.print("para dispensar");
      }
      
      break;

    default:
      break;
    }  
}

//---------------------------------FUNCTIONS------------------------------------

void tick(){
  // door_button.tick();
  // disp_button.tick();
}

