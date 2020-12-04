
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

/**************************** INICIO DE CONFIGURACION *************************/

#define PRODUCTO_INICIAL          0
#define PESO_DEFAULT              150
#define TIEMPO_ESPERA             1       // Segundos después de vaciar tolva

// Actuador para puerta
#define MODO_MOTOR
//#define MODO_SERVO

// Posiciones para servo EN GRADOS
#define DOOR_CLOSED               0
#define DOOR_OPEN                 90

// Voltaje para motor
// Rango (0-255)
//         Nada de movimiento <--0  255--> Máxima potencia
#define VELOCIDAD_APERTURA        255
#define VELOCIDAD_CIERRE          255

// Tiempos para muestreo de la báscula
#define FRECUENCIA_BASCULA        80

// Controla la sensibilidad de la báscula
// 1 = Lo más sensible      10 = Lo menos sensible
#define SENSIBILIDAD_DISPENSADO   3
#define SENSIBILIDAD_VACIADO      12

// Confuración de la báscula para transformar en gramos
#define SCALE_GRAMS               216

// Frecuencia de chicharra
#define FRECUENCIA_FALLA         10
#define FRECUENCIA_PASA          20

// Error de peso permisible
#define ERROR_PERMISIBLE          30

// Tiempo de señal controlado por Relay en Segundos
#define TIEMPO_DE_RELAY           2
// Tiempo a esperar justo después de dispensar en tolva
#define TIEMPO_DESPUES_DISP       1

// Tiempo de espera para evitar falsos positivos en las flechas
#define PAUSA_FLECHAS             500

/****************************** FIN DE CONFIGURACION **************************/

/************** ADVERTENCIA: NO MODIFIQUE EL RESTO DEL DOCUMENTO **************/

/******************************* Pinout definition ****************************/

// Vibrator output pin
#define VIBRATOR_PIN              2

// Door actuator control
#ifdef MODO_SERVO
#define SERVO_PIN                 4
#endif

#ifdef MODO_MOTOR
#define DC_CW_PIN                 4
#endif

#define DC_CCW_PIN                5

// Relay pinout
#define RELAY4_PIN                14
#define RELAY3_PIN                15
#define RELAY2_PIN                16
#define RELAY1_PIN                17

// Button pinout
#define DISPENSE_BUTTON_PIN       31
#define UP_BUTTON_PIN             33
#define RIGHT_BUTTON_PIN          35
#define DOWN_BUTTON_PIN           37
#define LEFT_BUTTON_PIN           39
#define ENTER_BUTTON_PIN          41
#define CANCEL_BUTTON_PIN         43
#define BUTTON8_PIN               45
#define BUTTON9_PIN               47
#define BUTTON10_PIN              49

// HX711 Load cell amplifier pinout
#define LOADCELL_DOUT_PIN         51
#define LOADCELL_SCK_PIN          53

// LCD definition 
#define LCD_COL                   16
#define LCD_ROW                   2

// Keypad resistor values
#define RIGHT_VALUE               60
#define UP_VALUE                  200
#define DOWN_VALUE                400
#define LEFT_VALUE                600
#define SELECT_VALUE              800

// Enum for Screens
enum class Screen{
    SPLASH=0,
    STANDBY,
    TARE,
    SETSPEED1,
    SETSPEED2,
    SETSPEEDCHANGE,
    SETPRODUCT,
    DISPENSING,
    SERVED,
    OPENDOOR,
    SETWEIGHT,
    ERRORSCREEN
};

// namespace vibration_dispenser definition
namespace vibration_dispenser{} 

#endif