
#ifndef UTILITIES_H_
#define UTILITIES_H_

// CONFIGURE AQUI
#define VEL1                250
#define VEL2                115
#define CAMBIO_VELOCIDAD    80
#define PESO_DEFAULT        1000

// Pinout definition
#define KEYPAD_PIN          A0
#define DOOR_BUTTON_PIN     29
#define DISPENSE_BUTTON_PIN 37
#define SERVO_PIN           2

#define pin_RS              8
#define pin_EN              9
#define pin_d4              4
#define pin_d5              5
#define pin_d6              6
#define pin_d7              7
#define pin_BL              10

#define LOADCELL_DOUT_PIN   53
#define LOADCELL_SCK_PIN    51

// LCD definition 
#define LCD_COL             16
#define LCD_ROW             4

// Servo positions
#define DOOR_CLOSED         0
#define DOOR_OPEN           90
// Scale definition
#define SCALE_GRAMS         257

// Keypad resistor values
#define RIGHT_VALUE         60
#define UP_VALUE            200
#define DOWN_VALUE          400
#define LEFT_VALUE          600
#define SELECT_VALUE        800

// Vibrator output pin
#define VIBRATOR_PIN        3

// Relays
#define RELAY1              46

// namespace vibration_dispenser definition
namespace vibration_dispenser{} 

#endif