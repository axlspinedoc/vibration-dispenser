#include <Arduino.h>
#include "../lib/inc/utilites.h"
#include "../lib/state_machine/state_machine.h"
#include "../lib/io/button.h"
#include <Wire.h>


using namespace vibration_dispenser;

control::State_machine machine_state;
io::Button door_button;

char incomingChar;
int weight=0;
bool weight_changed=false;

void setup() {
  
  Serial.begin(115200);
  Serial.println("System initialized");

  #ifdef PINOUT_ENABLE
  pinMode(DOOR_BUTTON, INPUT);
  pinMode(KEYPAD_PIN, INPUT);
  Servo door_servo;
  door_servo.attach(SERVO_PIN);
  #endif
  
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
      if (incomingChar=='S')
      {
        /* code */
        machine_state.setState(control::State::SERVED);
        Serial.println("State:= SERVED");
      }
      break;  

    case control::State::SERVED:
      if (incomingChar=='F')
      {
        /* code */
        machine_state.setState(control::State::FLUSH);
        Serial.println("State:= FLUSH");      
      }
      break;

    case control::State::FLUSH:
      if (incomingChar=='R')
      {
        /* code */
        machine_state.setState(control::State::STANDBY);
        Serial.println("State:= STANDBY");
      }
      
      break;

    default:
      break;
    }  
}

//---------------------------------FUNCTIONS------------------------------------




  


