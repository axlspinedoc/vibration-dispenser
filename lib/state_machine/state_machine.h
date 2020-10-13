//------------------------------------------------------------------------------
// @file: template.h
// @created on: April 23, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// IFNDEF ----------------------------------------------------------------------
#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

// DEFINES ---------------------------------------------------------------------

// INCLUDES --------------------------------------------------------------------

// FOWARD DECLARATIONS ---------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace control {  

// FOWARD DECLARATIONS ---------------------------------------------------------

// ENUMS -----------------------------------------------------------------------
enum class State{
  STANDBY=0,
  SETGRAMS,
  TARE,
  SETSPEED1,
  SETSPEED2,
  SETSPEEDCHANGE,
  SETPRODUCT,
  DISPENSING,
  SERVED,
  FLUSH,
  ERROR
};

// STRUCTS ---------------------------------------------------------------------

// TYPEDEFS --------------------------------------------------------------------

// CLASS DECLARATION -----------------------------------------------------------
class State_machine {
public:

  // CONSTRUCTOR AND DESTRUCTOR ------------------------------------------------
  /**
   * Constructor
   * */
  State_machine();
  /**
   * Destructor
   * */
  ~State_machine();

  // FUNCTIONS -----------------------------------------------------------------
  
  /**
   * Sets grams to dispense for next serving
   * @param grams[in]: grams wanted to dispense on next serving
   * @return 0 if function set a valid number, else ERROR. 
   * */
  int setGrams(int grams);

  /**
   * Set next state
   * @param State[in]: next State to change to
   * @return 0 if function set a valid State, else ERROR. 
   * */
  int setState(State next_state);
  
  /**
   * Gets current state   
   * @return 0 if there are no known errors
   * */
  State getState();
  
  
private:
  // FUNCTIONS -----------------------------------------------------------------  

  // MEMBERS -------------------------------------------------------------------
  int grams_programmed_ = 0;
  State state_;
  

}; // End of class Template

// END OF NAMESPACES 
}}
#endif
