
//------------------------------------------------------------------------------
// @file: utilities.h
// @author: Axel Sandoval
// @e-mail: axel_isc@hotmail.com
// @created on: September 15, 2020
// 
//
// @brief: Configurations used for the operation of the equipment
// LICENCE
//------------------------------------------------------------------------------

#ifndef UTILITIES_H_
#define UTILITIES_H_

// CONFIGURE AQUI
#define PRODUCTO_INICIAL          0
#define PESO_DEFAULT              1000
#define TIEMPO_ESPERA             2       // Segundos después de vaciar tolva

// Para seleccionar el modo del relevador, remover las diagonales y 
// colocarlas en el modo a desactivar
#define MODO_ALARMA
//#define MODO_MOTOR

// Posiciones para servo EN GRADOS
#define DOOR_CLOSED               0
#define DOOR_OPEN                 90

// Controla la sensibilidad de la báscula
// 1 = Lo más sensible      10 = Lo menos sensible
#define SENSIBILIDAD_DISPENSADO   5
#define SENSIBILIDAD_VACIADO      4

// Confuración de la báscula para transformar en gramos
#define SCALE_GRAMS               216

// Tiempo de señal controlado por Relay en Segundos
#define TIEMPO_DE_RELAY           2

// Tiempo a esperar justo después de dispensar en tolva
#define TIEMPO_DESPUES_DISP       2

// Tiempo de espera para evitar falsos positivos en las flechas
#define PAUSA_FLECHAS             500

// Pinout definition
#define KEYPAD_PIN                A0
#define CANCEL_BUTTON_PIN         29
#define DISPENSE_BUTTON_PIN       37
#define SERVO_PIN                 3

#define pin_RS                    8
#define pin_EN                    9
#define pin_d4                    4
#define pin_d5                    5
#define pin_d6                    6
#define pin_d7                    7
#define pin_BL                    10

#define LOADCELL_DOUT_PIN         53
#define LOADCELL_SCK_PIN          51

// LCD definition 
#define LCD_COL                   16
#define LCD_ROW                   2


// Keypad resistor values
#define RIGHT_VALUE               60
#define UP_VALUE                  200
#define DOWN_VALUE             400
#define LEFT_VALUE                600
#define SELECT_VALUE              800

// Vibrator output pin
#define VIBRATOR_PIN           2

// Relays
#define RELAY1                    46

// namespace vibration_dispenser definition
namespace vibration_dispenser{} 

#endif