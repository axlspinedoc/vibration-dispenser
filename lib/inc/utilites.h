
#ifndef UTILITIES_H_
#define UTILITIES_H_

// Pinout definition
#define KEYPAD_PIN          A0
#define DOOR_BUTTON_PIN     5
#define DISPENSE_BUTTON_PIN 31
#define SERVO_PIN           3

// LCD Size 
#define LCD_COL             16
#define LCD_ROW             4
// I2C LCD  
#define LCD_ADDRESS         0x3F
// Common LCD
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 

// Definition of custom values
#define DOOR_CLOSED     0
#define DOOR_OPEN       45

#define RIGHT_VALUE     60
#define UP_VALUE        200
#define DOWN_VALUE      400
#define LEFT_VALUE      600
#define SELECT_VALUE    800

// Modes for operation
// #define PINOUT_ENABLE

#endif

// namespace vibration_dispenser definition
namespace vibration_dispenser{} 