//------------------------------------------------------------------------------
// @file: template.h
// @created on: April 23, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// IFNDEF ----------------------------------------------------------------------
#ifndef TEMPLATE_H_
#define TEMPLATE_H_

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
  SELECT
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
   * @return whatever it returns. 
   * */
  void publicFunction(const long &value = 0);  

  /**
   * Brief of the function 
   * @param value[in]: Input value
   * @return whatever it returns. 
   * */
  Key getKey();
  
private:

  // MEMBERS -------------------------------------------------------------------  
  
  // saves pin where keypad is attached
  int keypad_pin_;
  
}; // End of class Template

// END OF NAMESPACES 
}}
#endif
