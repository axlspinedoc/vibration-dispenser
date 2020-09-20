//------------------------------------------------------------------------------
// @file: template.h
// @created on: April 23, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// IFNDEF ----------------------------------------------------------------------
#ifndef KEYPAD_H_
#define KEYPAD_H_

// DEFINES ---------------------------------------------------------------------

// INCLUDES --------------------------------------------------------------------
#include "../inc/utilites.h"
#include <Arduino.h>

// FOWARD DECLARATIONS ---------------------------------------------------------

// ENUM ------------------------------------------------------------------------
enum class Key{
  RIGHT=0,
  UP,
  DOWN,
  LEFT,
  SELECT,
  NO_KEY
};

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace io {  

// CLASS DECLARATION -----------------------------------------------------------
class Keypad {
public:

  // CONSTRUCTOR AND DESTRUCTOR ------------------------------------------------
  /**
   * Constructor
   * */
  Keypad(int pinout,unsigned long debounceDelay=500);
  /**
   * Destructor
   * */
  ~Keypad();

  // FUNCTIONS -----------------------------------------------------------------
  /**
   * Brief of the function 
   * @param value[in]: Input value
   * @return whatever it returns. 
   * */
  void publicFunction(const long &value = 0);  

  /**
   * Brief of the function 
   * @param value[in]: Input value
   * @return Key registered
   * */
  Key getKey();
  
private:

  /**
   * Checks which key is pressed at the moment   
   * @return Key registered
   * */
  Key checkKeys();

  // MEMBERS -------------------------------------------------------------------  
  
  // saves pin where keypad is attached
  int keypad_pin_;
  // The binary output of the button 
  Key output_key_=Key::NO_KEY;
  // The actual state of the pin
  Key key_state_;
  // The previous state of the Keypad
  Key last_key_state_=Key::NO_KEY;
  // the last time a change in key state was recorded
  unsigned long lastDebounceTime_=0;  
  // the debounce time in millis; increase if the output flickers  
  unsigned long debounceDelay_;
  
}; // End of class Template

// END OF NAMESPACES 
}}
#endif
