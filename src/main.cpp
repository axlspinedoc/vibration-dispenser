#include <Arduino.h>
#include "../lib/inc/utilites.h"

using namespace vibration_dispenser;

enum class State{
  STANDBY=0,
  SETGRAMS=1,
  DISPENSING=2,
  SERVED=3,
  FLUSH=4
};

char incomingChar;
int weight=0;
bool weight_changed=false;

State state;

void setup() {
  
  Serial.begin(115200);
  Serial.println("System initialized");
  
  state=State::STANDBY;
  Serial.println("State:= STANDBY");

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
  
    switch (state)
    {
    case State::STANDBY:
      if (incomingChar=='W')
      {
        /* code */
        state=State::SETGRAMS;
        Serial.println("State:= SETGRAMS");
      } else if(incomingChar=='D'){

      state=State::DISPENSING;
      Serial.println("State:= DISPENSING");
      }     
      break;
    
    case State::SETGRAMS:
      
      if (weight_changed)
      {
        Serial.print("Weight set to= ");
        Serial.println(weight);
        weight_changed=false;
      }    
      
      if (incomingChar=='Q')
      {
        /* code */
        state=State::STANDBY;
        Serial.println("State:= STANDBY");
      }
      break;

    case State::DISPENSING:
      if (incomingChar=='S')
      {
        /* code */
        state=State::SERVED;
        Serial.println("State:= SERVED");
      }
      break;  

    case State::SERVED:
      if (incomingChar=='F')
      {
        /* code */
        state=State::FLUSH;
        Serial.println("State:= FLUSH");      
      }
      break;

    case State::FLUSH:
      if (incomingChar=='R')
      {
        /* code */
        state=State::STANDBY;
        Serial.println("State:= STANDBY");
      }
      
      break;

    default:
      break;
    }  
}

//---------------------------------FUNCTIONS------------------------------------

void resolveSerial(){
  
}



  


