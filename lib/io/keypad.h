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
  Keypad(int pinout);
  /**
   * Destructor
   * */
  ~Keypad();

  // FUNCTIONS -----------------------------------------------------------------
  
  /**
   * Brief of the function 
   * @param value[in]: Input value
   * @return Key registered
   * */
  Key getKey();
  

  void resetKeys();

private:
  /**
   * Checks which key is pressed at the moment   
   * @return Key registered
   * */
  Key checkKeys();

  // MEMBERS -------------------------------------------------------------------  
  
  // saves pin where keypad is attached
  int keypad_pin_;
  // The previous state of the Keypad
  Key last_key_state_=Key::NO_KEY;

  Key output_key_=Key::NO_KEY;
  
}; // End of class Template

// END OF NAMESPACES 
}}
#endif
