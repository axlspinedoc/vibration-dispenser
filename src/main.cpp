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

State state;

void setup() {
  
  Serial.begin(115200);
  state=State::STANDBY;
  Serial.write("System initialized");

}

void loop() {

  switch (state)
  {
  case State::STANDBY:
    /* code */
    break;
  
  case State::SETGRAMS:
    /* code */
    break;

  case State::DISPENSING:
    /* code */
    break;  

  case State::SERVED:
    /* code */
    break;

  case State::FLUSH:
    /* code */
    break;

  default:
    break;
  }

}



  


