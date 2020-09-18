//------------------------------------------------------------------------------
// @file: template.h
// @created on: April 23, 2020
// 
// LICENCE
//------------------------------------------------------------------------------

// IFNDEF ----------------------------------------------------------------------
#ifndef SCREENCOM_H_
#define SCREENCOM_H_

// DEFINES ---------------------------------------------------------------------
#include "../inc/utilites.h"
#include "LiquidCrystal_I2C.h"

// INCLUDES --------------------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace io {  

LiquidCrystal_I2C lcd(LCD_ADDRESS,20,4);

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
   * Brief of the function 
   * @param value[in]: Input value
   * @return whatever it returns. 
   * */
  void publicFunction(const long &value = 0);
  
private:
  // FUNCTIONS -----------------------------------------------------------------
  
  // MEMBERS -------------------------------------------------------------------
    

}; // End of class Template

// END OF NAMESPACES 
}}
#endif
