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
#include "../lib/io/keypad.h"

using namespace vibration_dispenser;

control::State_machine machine_state;
io::Button door_button(DOOR_BUTTON_PIN,100);
io::Button disp_button(DISPENSE_BUTTON_PIN,100);
io::Keypad interface(KEYPAD_PIN);

HX711 scale;
Servo door_servo;


// TODO: Refactor inside screencom class
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

// TODO: Refactor inside Serial_Debug class
// Serial comm DEBUGGING
char incomingChar;
int weight=1000;
int read_weight;
int new_weight;

// TODO: Refactor inside screencom class
// Forward definitions of Screencom
void setScreen(Screen menu, int old_weight=0, int new_weight=0);
void splashScreen();
void standbyScreen();
void dispensingScreen();
void servedScreen();
void openDoorScreen();
void setWeightScreen(int old_weight, int new_weight, int col = 14);
void weightConfirmedScreen();
void errorScreen();
int manageWeight(int saved_weight);

// Forward definitions of vibrator
void setVibration(int percentage);

void setup() {
  
  Serial.begin(115200);
  Serial.println("System initialized");
  door_servo.attach(SERVO_PIN);
  door_servo.write(DOOR_CLOSED);

  if (scale.is_ready())
  {
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  
    scale.set_scale(SCALE_GRAMS);
    scale.tare();        
  }else{
    // This should be an Error condition
    Serial.println("Scale not detected");
  }
    
  // Screencom
  lcd.begin(LCD_COL,LCD_ROW);
  setScreen(Screen::SPLASH);
  delay(500);
  machine_state.setState(control::State::STANDBY);
  setScreen(Screen::STANDBY);  
  
  // Vibrator
  pinMode(VIBRATOR_PIN, OUTPUT);

  // Relays
  pinMode(RELAY1,OUTPUT);
}

void loop() {
    
  if (Serial.available()>0)
  {
    if (Serial.available()==1)
    {
      // Single key: Next Stage
      incomingChar=Serial.read();
    }    
  }
  
    switch (machine_state.getState())
    {
    case control::State::STANDBY:
      disp_button.update();
      
      if (incomingChar=='W' || interface.getKey()==Key::SELECT)
      {
        interface.resetKeys();
        machine_state.setState(control::State::SETGRAMS);
        Serial.println("State:= SETGRAMS");
        setScreen(Screen::SETWEIGHT,weight,weight);
        
      }

      if(incomingChar=='D' || disp_button.getState()){
        disp_button.reset();
        machine_state.setState(control::State::DISPENSING);        
        Serial.println("State:= DISPENSING"); 
        setScreen(Screen::DISPENSING);                
      }     
      break;
    
    case control::State::SETGRAMS:

      new_weight=manageWeight(weight);
      incomingChar='Q'; // Forces exit of state
      if (new_weight!=weight)
      {
          weight=new_weight;
          weightConfirmedScreen();
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
      // TODO: Add "scale.is_ready() for protection and avoid hanging"
      read_weight = scale.get_units();
      lcd.setCursor(0,1);
      lcd.print("     ");
      lcd.setCursor(0,1);      
      lcd.print(read_weight);
      
      
      if ((read_weight>=weight) || disp_button.getState())      
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


void setScreen(Screen menu, int old_weight, int new_weight){
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
    setWeightScreen(old_weight,new_weight);
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
void setWeightScreen(int old_weight, int new_weight, int col){
  lcd.clear();
  lcd.print("Peso prog.");
  lcd.setCursor(0,1);
  lcd.print("Nuevo peso");
  lcd.setCursor(15,0);
  lcd.print("g");
  lcd.setCursor(15,1);
  lcd.print("g");
  
  if (new_weight<10)
  {        
    lcd.setCursor(14,1);
  }else if(new_weight<100){    
    lcd.setCursor(13,1);
  }else if (new_weight<1000){
    lcd.setCursor(12,1);
  } else {
    lcd.setCursor(11,1);
  }
  lcd.print(new_weight);
  

  if (old_weight<10)
  {        
    lcd.setCursor(14,0);
  }else if(old_weight<100){    
    lcd.setCursor(13,0);
  }else if (old_weight<1000){
    lcd.setCursor(12,0);
  } else {
    lcd.setCursor(11,0);
  }
  lcd.print(old_weight);
  
  lcd.setCursor(col,1);
  lcd.blink();
}

// Manages weight change screen. Allows user to change desired weight digit by
// digit.
int manageWeight(int saved_weight){
    
    int set_weight=saved_weight;
    int col=14;
    int increments[4] = {1,10,100,1000};    
    
    while (interface.getKey()!=Key::SELECT)
    {
        switch (interface.getKey())
        {
        case Key::RIGHT:              
            interface.resetKeys();                    
                if (col<14)
                {            
                    ++col;
                    lcd.setCursor(col,1);
                }        
            break;
        case Key::UP:              
            interface.resetKeys();        
            Serial.println("UP");
            set_weight += increments[14-col];
            if (set_weight>=2000)
            {
                set_weight=2000;
            }                        
            setWeightScreen(saved_weight,set_weight,col);
            break;
        case Key::DOWN:              
            interface.resetKeys();        
            Serial.println("DOWN");
            set_weight -= increments[14-col];
            if (set_weight<=0)
            {
                set_weight=0;
            }                        
            setWeightScreen(saved_weight,set_weight,col);
            break;
        case Key::LEFT:        
            interface.resetKeys();                            
                if (col>11)
                {            
                    --col;
                    lcd.setCursor(col,1);
                }
            break;        
        
        default:        
            break;
            }    
        }
    interface.resetKeys();
    return set_weight;       
}

void weightConfirmedScreen(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("|Peso  cambiado|");
    lcd.setCursor(0,1);
    lcd.print("| exitosamente |");
    delay(1500);
}

void setVibration(int percentage){
  int pwm=map(percentage,0,100,0,255);
  analogWrite(VIBRATOR_PIN,pwm);
}

void errorScreen(){
  //TO DO: Define Error codes and screen
}

//------------------------------END OF PROGRAM----------------------------------