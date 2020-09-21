
#ifndef UTILITIES_H_
#define UTILITIES_H_

// Pinout definition
#define KEYPAD_PIN          A0
#define DOOR_BUTTON_PIN     30
#define DISPENSE_BUTTON_PIN 31
#define SERVO_PIN           44

#define pin_RS              8
#define pin_EN              9
#define pin_d4              4
#define pin_d5              5
#define pin_d6              6
#define pin_d7              7
#define pin_BL              10

#define LOADCELL_DOUT_PIN   52
#define LOADCELL_SCK_PIN    53

// LCD definition 
#define LCD_COL             16
#define LCD_ROW             4

// Servo positions
#define DOOR_CLOSED         0
#define DOOR_OPEN           45

// Scale definition
#define SCALE_GRAMS         257

// Keypad resistor values
#define RIGHT_VALUE         60
#define UP_VALUE            200
#define DOWN_VALUE          400
#define LEFT_VALUE          600
#define SELECT_VALUE        800

// namespace vibration_dispenser definition
namespace vibration_dispenser{} 

#endif