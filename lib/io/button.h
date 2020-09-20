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
   * Assigns attach pin and custom debounce delay time; ifnot defaults to 50ms
   * */
  Button(int button_pin_, unsigned long debounceDelay=80);
  /**
   * Destructor
   * */
  ~Button();

  // FUNCTIONS -----------------------------------------------------------------
  /**
   * get button state AFTER debounce time  
   * @return true when condition is met after debounce time, false if else
   * */
  bool getState();

  // FUNCTIONS -----------------------------------------------------------------
  /**
   * Constantly checks for a state change in the pin. After completing debounce
   * time, output state changes to true. Output state must be reset after read.   
   * */
  void update();

  // FUNCTIONS -----------------------------------------------------------------
  /**
   * Resets output state to 0   
   * */
  void reset();
  
private:  

  // MEMBERS -------------------------------------------------------------------
  
  // saves pin where button is attached
  int button_pin_;
  // The binary output of the button 
  int output_state_=false;
  // The actual state of the pin
  int button_state_;
  // The previous state of the pin
  int last_button_state_=HIGH;
  // the last time a change in pin state was recorded
  unsigned long lastDebounceTime_=0;  
  // the debounce time in millis; increase if the output flickers  
  unsigned long debounceDelay_;
}; // End of class Template

// END OF NAMESPACES 
}}
#endif
