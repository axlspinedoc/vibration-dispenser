//------------------------------------------------------------------------------
// @file: Screencom.h
// @created on: September 18, 2020
// @author: Axel Sandoval
// @e-mail: axel_isc@hotmail.com
// @brief: Screen manager for LCD's, manages menus, animations and visual
// effects
// 
// LICENCE
//------------------------------------------------------------------------------

// IFNDEF ----------------------------------------------------------------------
#ifndef SCREENCOM_H_
#define SCREENCOM_H_

// DEFINES ---------------------------------------------------------------------

// INCLUDES --------------------------------------------------------------------
#include "../Keypad_shield/LiquidCrystal.h"
#include "../inc/utilites.h"

// FOWARD DECLARATIONS ---------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace io {  

// FOWARD DECLARATIONS ---------------------------------------------------------

// ENUMS -----------------------------------------------------------------------
enum class Screen{
    STANDBY=0,
    DISPENSING,
    SERVED,
    OPENDOOR,
    SETWEIGHT,
    ERRORSCREEN
};

// CLASS DECLARATION -----------------------------------------------------------
class Screencom {
public:

  // CONSTRUCTOR AND DESTRUCTOR ------------------------------------------------
  /**
   * Constructor
   * */
  Screencom();
  /**
   * Destructor
   * */
  ~Screencom();

  // FUNCTIONS -----------------------------------------------------------------
  /**
   * Function that sets the screen to be displayed
   * @param menu[in]: Screen to display   
   * */
  void setScreen(Screen menu);  
  
private:
  // FUNCTIONS -----------------------------------------------------------------

  void splashScreen();
  
  void standbyScreen();

  void dispensingScreen();

  void servedScreen();

  void openDoorScreen();

  void setWeightScreen();

  void errorScreen();

  // MEMBERS -------------------------------------------------------------------
  
  
}; // End of class Template

// END OF NAMESPACES 
}}
#endif
