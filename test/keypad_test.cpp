//------------------------------------------------------------------------------
// @file: main.cpp
// @author: Axel Sandoval
// @e-mail: axel_isc@hotmail.com
// @created on: September 15, 2020
// 
//
// @brief: Source code for a vibration dispenser machine with scalability.
// LICENCE
//------------------------------------------------------------------------------

#include <Arduino.h>
#include <Servo.h>
#include "../lib/inc/utilites.h"
#include "../lib/state_machine/state_machine.h"
#include "../lib/io/button.h"
#include "../lib/scale/HX711.h"
#include "../lib/io/screencom.h"
//#include "../lib/io/keypad.h"

using namespace vibration_dispenser;

control::State_machine machine_state;
io::Button door_button(DOOR_BUTTON_PIN,100);
io::Button disp_button(DISPENSE_BUTTON_PIN,100);

HX711 scale;
Servo door_servo;

// io::Keypad keypad(KEYPAD_PIN);

// Screencom
LiquidCrystal lcd(pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
enum class Screen{
    SPLASH=0,
    STANDBY,
    DISPENSING,
    SERVED,
    OPENDOOR,
    SETWEIGHT,
    ERRORSCREEN
};

// Serial comm DEBUGGING
char incomingChar;
int weight=1000;
bool weight_changed=false;
long read_weight;

// Forward definitions of Screencom
void setScreen(Screen menu);
void splashScreen();
void standbyScreen();
void dispensingScreen();
void servedScreen();
void openDoorScreen();
void setWeightScreen();
void errorScreen();

void setup() {
  
  Serial.begin(115200);
  Serial.println("System initialized");
  door_servo.attach(SERVO_PIN);
  door_servo.write(DOOR_CLOSED);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  
  scale.set_scale(SCALE_GRAMS);
  scale.tare();  
  
  // Screencom
  lcd.begin(LCD_COL,LCD_ROW);
  setScreen(Screen::SPLASH);
  delay(800);
  machine_state.setState(control::State::STANDBY);
  setScreen(Screen::STANDBY);
  
  
}

void loop() {
    
  if (Serial.available()>0)
  {
    if (Serial.available()==1)
    {
      // Single key: Next Stage
      incomingChar=Serial.read();
    }else{
      // Char chain: Set Weight
      
      int bytesAvailable=Serial.available();          
      String serialBuffer="";

      for (int idx = 0; idx<bytesAvailable;  idx++) {            
        char input_char = Serial.read();            
        serialBuffer = serialBuffer + input_char;            
        }
      weight=serialBuffer.toInt();
      weight_changed=true;
      
    }
    
  }
  
    switch (machine_state.getState())
    {
    case control::State::STANDBY:
      disp_button.update();
      
      if (incomingChar=='W')
      {
        machine_state.setState(control::State::SETGRAMS);
        Serial.println("State:= SETGRAMS");
        setScreen(Screen::SETWEIGHT);
        
      } else if(incomingChar=='D' || disp_button.getState()){
        disp_button.reset();
        machine_state.setState(control::State::DISPENSING);        
        Serial.println("State:= DISPENSING"); 
        setScreen(Screen::DISPENSING);                
      }     
      break;
    
    case control::State::SETGRAMS:
      
      if (weight_changed)
      {
        Serial.print("Weight set to= ");
        Serial.println(weight);
        weight_changed=false;
      }    
      
      if (incomingChar=='Q')
      {        
        machine_state.setState(control::State::STANDBY);
        Serial.println("State:= STANDBY");
        setScreen(Screen::STANDBY);
      }
      break;

    case control::State::DISPENSING:
      
      disp_button.update();
      read_weight = scale.get_units();
      lcd.setCursor(0,1);
      lcd.print("     ");
      lcd.setCursor(0,1);      
      lcd.print(read_weight);
      
      
      if ((read_weight>=weight) || disp_button.getState())
      //if (disp_button.getState())
      {        
        disp_button.reset();
        machine_state.setState(control::State::SERVED);        
        setScreen(Screen::SERVED);
        Serial.println("State:= SERVED");
      }
      break;  

    case control::State::SERVED:
      door_button.update();             
      if (incomingChar=='F' || door_button.getState())
      {        
        door_button.reset();
        machine_state.setState(control::State::FLUSH);        
        door_servo.write(DOOR_OPEN);      
        setScreen(Screen::OPENDOOR); 
        Serial.println("State:= FLUSH");
      }
      break;

    case control::State::FLUSH:      
      door_button.update();
      if (incomingChar=='R' || door_button.getState())
      {        
        door_button.reset();
        machine_state.setState(control::State::STANDBY);        
        door_servo.write(DOOR_CLOSED);
        setScreen(Screen::STANDBY);
        Serial.println("State:= STANDBY");
      }
      
      break;

    default: //Unknown State, shouldn't be reachable. Must prompt error.
        machine_state.setState(control::State::ERROR);     
      break;
    }  
}

//---------------------------------FUNCTIONS------------------------------------


void setScreen(Screen menu){
  if (menu!=Screen::SETWEIGHT)
  {
    lcd.noBlink();
  }
  
  switch (menu)
  {
  case Screen::SPLASH:
    splashScreen();
    break;
  case Screen::STANDBY:
    standbyScreen();
    break;
  case Screen::SETWEIGHT:
    setWeightScreen();
    break;
  case Screen::DISPENSING:
    dispensingScreen();
    break;
  case Screen::SERVED:
    servedScreen();
    break;
  case Screen::OPENDOOR:
    openDoorScreen();
    break;
  case Screen::ERRORSCREEN:
    errorScreen();
    break;
  
  default:
    break;
  }
  
}  
void splashScreen(){
  lcd.clear();    
  lcd.setCursor(0,0);  
  lcd.print("Sistema iniciado");
  lcd.setCursor(0,1);
  lcd.print("V0.1");
  delay(2000);
}
void standbyScreen(){  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Presione D");
  lcd.setCursor(0,1);
  lcd.print("para dispensar");
}
void dispensingScreen(){
  lcd.clear();
  lcd.print("Dispensando...");
}
void servedScreen(){
  lcd.clear();
  lcd.print("Presione F para");   
  lcd.setCursor(0,1);
  lcd.print("vaciar tolva");
}
void openDoorScreen(){
  lcd.clear();
  lcd.print("Presione R para"); 
  lcd.setCursor(0,1);
  lcd.print("terminar vaciado");
}
void setWeightScreen(){
  lcd.clear();
  lcd.print("Peso prog.");
  if (weight<1000)
  {
    lcd.setCursor(12,0);
    lcd.print(weight);
    lcd.print("g");
    lcd.setCursor(0,1);
    lcd.print("Nuevo peso");
    lcd.setCursor(12,1);
    lcd.print(weight);
    lcd.print("g");
    lcd.setCursor(12,1);
    lcd.blink();    
  }else{
    lcd.setCursor(11,0);
    lcd.print(weight);
    lcd.print("g");
    lcd.setCursor(0,1);
    lcd.print("Nuevo peso");
    lcd.setCursor(11,1);
    lcd.print(weight);
    lcd.print("g");
    lcd.setCursor(11,1);
    lcd.blink();
  }
}

void errorScreen(){
  //TO DO: Define Error codes and screen
}

//------------------------------END OF PROGRAM----------------------------------