//------------------------------------------------------------------------------
// @file: template.cpp
// @created on: May 4, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// INCLUDES --------------------------------------------------------------------
#include "state_machine.h"
// FOWARD DECLARATIONS ---------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace control {  

// ENUMS -----------------------------------------------------------------------

// STRUCTS ---------------------------------------------------------------------

// CLASS IMPLEMENTATION --------------------------------------------------------

State_machine::State_machine() {
  state_=State::STANDBY;
}
  
State_machine::~State_machine() {

}

int State_machine::setGrams(int grams) {
  grams_programmed_=grams;
  return 0;
}

int State_machine::setState(State next_state){
  
  return 0;
}

State State_machine::getState(){
  return state_;
}
  
// END OF NAMESPACES -----------------------------------------------------------
}}