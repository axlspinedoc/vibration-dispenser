#include <Arduino.h>
//#include "../lib/io/button.h"
#include <Servo.h>
#include <Wire.h>
#include "../lib/MHAdapter/LiquidCrystal_I2C.h"
#include "../lib/inc/utilites.h"
#include "../lib/state_machine/state_machine.h"

using namespace vibration_dispenser;

control::State_machine machine_state;

char incomingChar;
int weight=0;
bool weight_changed=false;

Servo door_servo;
LiquidCrystal_I2C lcd(LCD_ADDRESS,20,4);

void setup() {
  
  Serial.begin(115200);
  Serial.println("System initialized");
  door_servo.attach(3);
  door_servo.write(0);
  
  lcd.begin();
  lcd.clear();  
  lcd.setCursor(1,1);
  lcd.print("System initialized");
  lcd.setCursor(1,3);
  lcd.print("V0.1");
  delay(2000);

  #ifdef PINOUT_ENABLE  
  Servo door_servo;
  door_servo.attach(SERVO_PIN);
  #endif

  //lcd.print("System initialized");
}

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
      lcd.clear();
      lcd.print("Presione D para dispensar");
      lcd.setCursor(0,3);      
      lcd.print("Presione W para cambiar gramaje");

      if (incomingChar=='W')
      {
        /* code */
        machine_state.setState(control::State::SETGRAMS);
        Serial.println("State:= SETGRAMS");
        
      } else if(incomingChar=='D'){

        machine_state.setState(control::State::DISPENSING);
        Serial.println("State:= DISPENSING");              
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
        /* code */
        machine_state.setState(control::State::STANDBY);
        Serial.println("State:= STANDBY");
      }
      break;

    case control::State::DISPENSING:
      lcd.clear();
      lcd.print("Dispensando");      
      lcd.setCursor(0,3);      
      lcd.print("Presione S para terminar de dispensar");
      
      if (incomingChar=='S')
      {
        /* code */
        machine_state.setState(control::State::SERVED);
        Serial.println("State:= SERVED");
      }
      break;  

    case control::State::SERVED:
      lcd.clear();
      lcd.print("Presione F para vaciar tolva");      
      
      if (incomingChar=='F')
      {
        /* code */
        machine_state.setState(control::State::FLUSH);
        Serial.println("State:= FLUSH");
        door_servo.write(90);      
      }
      break;

    case control::State::FLUSH:
      lcd.clear();
      lcd.print("Presione R para terminar vaciado");  
      
      if (incomingChar=='R')
      {
        /* code */
        machine_state.setState(control::State::STANDBY);
        Serial.println("State:= STANDBY");
        door_servo.write(0);
      }
      
      break;

    default:
      break;
    }  
}

//---------------------------------FUNCTIONS------------------------------------




  


