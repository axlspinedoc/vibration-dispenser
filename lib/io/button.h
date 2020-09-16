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

// FOWARD DECLARATIONS ---------------------------------------------------------

// NAMESPACES ------------------------------------------------------------------
namespace vibration_dispenser { namespace io {  

// FOWARD DECLARATIONS ---------------------------------------------------------

// ENUMS -----------------------------------------------------------------------

// STRUCTS ---------------------------------------------------------------------

// TYPEDEFS --------------------------------------------------------------------

// CLASS DECLARATION -----------------------------------------------------------
class Button {
public:

  // CONSTRUCTOR AND DESTRUCTOR ------------------------------------------------
  /**
   * Constructor
   * */
  Button();
  /**
   * Destructor
   * */
  ~Button();

  // FUNCTIONS -----------------------------------------------------------------
  /**
   * Brief of the function 
   * @param value[in]: Input value
   * @return whatever it returns. 
   * */
  void publicFunction(const long &value = 0);
  
  // MEMBER GETTERS ------------------------------------------------------------
  int getTemplateValue() const;

  // MEMBER SETTERS ------------------------------------------------------------
  void setTemplateValue(const int &templateValue);
  
private:
  // FUNCTIONS -----------------------------------------------------------------
  void privateFunction();

  // MEMBERS -------------------------------------------------------------------
  int templateValue_ = 0;
  const int templateConstValue = 10;
}; // End of class Template

// END OF NAMESPACES 
}}
#endif
