//------------------------------------------------------------------------------
// @file: button.h
// @author: Axel Sandoval
// @e-mail: axel_isc@hotmail.com
// @created on: September 17, 2020
// 
//
// @brief: Button library with debounce functionality. 
// LICENCE
//------------------------------------------------------------------------------

// IFNDEF ----------------------------------------------------------------------
#ifndef BUTTON_H_
#define BUTTON_H_

// INCLUDES --------------------------------------------------------------------
#include <Arduino.h>

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace io {  

// CLASS DECLARATION -----------------------------------------------------------
class Button {
public:

  // CONSTRUCTOR AND DESTRUCTOR ------------------------------------------------
  /**
   * Constructor
   * Assigns custom debounce delay time, ifnot, defaults to 50ms
   * */
  Button(int button_pin_, unsigned long debounceDelay=50);
  /**
   * Destructor
   * */
  ~Button();

  // FUNCTIONS -----------------------------------------------------------------
  /**
   * get button state AFTER debounce time  
   * @return true when condition is met after debounce time, false if else
   * */
  int getState();
  
private:  

  // MEMBERS -------------------------------------------------------------------
  
  // saves pin where button is attached
  int button_pin_;
  // 
  int current_state_=LOW;
  int last_state_=LOW;
  // the last time the output pin was toggled
  unsigned long lastDebounceTime_;  
  // the debounce time in millis; increase if the output flickers  
  unsigned long debounceDelay_;
}; // End of class Template

// END OF NAMESPACES 
}}
#endif
