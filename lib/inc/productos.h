//------------------------------------------------------------------------------
// @file: productos.h
// @author: Axel Sandoval
// @e-mail: axel_isc@hotmail.com
// @created on: October 11, 2020
// 
//
// @brief: Product list with parameters for selection from screen
// LICENCE
//------------------------------------------------------------------------------

/** Para agregar más productos: 
 * 1.- Aumente el número de productos 
 * 2.- En las características de dispensado asegurece de tener un renglon
 * por cada producto. Agregué el siguiente paréntesis:
 *  {  215,   115,    80}
 * para especificar las propiedades de dispensado del producto
 * 3.- En la sección de nombres agregue entre "comillas" el nombre de producto.
 * 4.- La posición del paréntesis de las propiedades de dispensado DEBE
 * coincidir con la posición del paréntesis del nombre del producto
 * 
*/

#define NUM_PRODUCTOS 5

namespace vibration_dispenser{

// Aquí definimos las características del dispensado
const int product_param[NUM_PRODUCTOS][3]{
    // Vel 1, Vel 2, % Cambio Vel
    {  210,   110,    80},
    {  211,   111,    81},
    {  212,   112,    82},
    {  213,   113,    83},
    {  214,   114,    84}
    
};

// Aquí definimos nombre del producto, cuidando que no exceda los 16 caracteres
const char product_name[NUM_PRODUCTOS][16]{
    "Arandano",
    "Cacahuate",
    "Frijol",
    "Lenteja",
    "Haba"
};

}