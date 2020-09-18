#include <Arduino.h>
#include <Servo.h>
#include "../lib/MHAdapter/LiquidCrystal_I2C.h"
#include "../lib/inc/utilites.h"
#include "../lib/state_machine/state_machine.h"

using namespace vibration_dispenser;

control::State_machine machine_state;

// Serial comm
char incomingChar;
int weight=0;
bool weight_changed=false;

// Screencom
bool published=false;

Servo door_servo;
LiquidCrystal_I2C lcd(LCD_ADDRESS,20,4);

void setup() {
  
  Serial.begin(115200);
  Serial.println("System initialized");
  door_servo.attach(SERVO_PIN);
  door_servo.write(DOOR_CLOSED);
  
  lcd.begin();
  lcd.clear();  
  lcd.setCursor(1,1);
  lcd.print("System initialized");
  lcd.setCursor(1,3);
  lcd.print("V0.1");
  delay(2000);

  lcd.clear();
  lcd.print("Presione D para");
  lcd.setCursor(0,1);
  lcd.print("dispensar");
  lcd.setCursor(0,2);      
  lcd.print("Presione W para");
  lcd.setCursor(0,3);
  lcd.print("cambiar gramaje");
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
      

      if (incomingChar=='W')
      {
        machine_state.setState(control::State::SETGRAMS);
        Serial.println("State:= SETGRAMS");
        
      } else if(incomingChar=='D'){

        machine_state.setState(control::State::DISPENSING);
        Serial.println("State:= DISPENSING");
        lcd.clear();
        lcd.print("Dispensando...");      
        lcd.setCursor(0,2);      
        lcd.print("Presione S para");
        lcd.setCursor(0,3);
        lcd.print("detener dispensado");                    
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
      }
      break;

    case control::State::DISPENSING:
      
      
      if (incomingChar=='S')
      {        
        machine_state.setState(control::State::SERVED);
        Serial.println("State:= SERVED");
        lcd.clear();
        lcd.print("Presione F para");   
        lcd.setCursor(0,1);
        lcd.print("vaciar tolva");
      }
      break;  

    case control::State::SERVED:
               
      if (incomingChar=='F')
      {        
        machine_state.setState(control::State::FLUSH);
        Serial.println("State:= FLUSH");
        door_servo.write(DOOR_OPEN);      
        lcd.clear();
        lcd.print("Presione R para"); 
        lcd.setCursor(0,1);
        lcd.print("terminar vaciado"); 
      }
      break;

    case control::State::FLUSH:      
      
      if (incomingChar=='R')
      {        
        machine_state.setState(control::State::STANDBY);
        Serial.println("State:= STANDBY");
        door_servo.write(DOOR_CLOSED);
        lcd.clear();
        lcd.print("Presione D para");
        lcd.setCursor(0,1);
        lcd.print("dispensar");
        lcd.setCursor(0,2);      
        lcd.print("Presione W para");
        lcd.setCursor(0,3);
        lcd.print("cambiar gramaje");
      }
      
      break;

    default:
      break;
    }  
}

//---------------------------------FUNCTIONS------------------------------------

void writeToScreen(String message){
  if (published)
  {      
    published=true;
    lcd.clear();
    
    if (message.length()>LCD_COL)
    {
      String String1=message.substring(0,LCD_COL);
      String String2=message.substring(LCD_COL+1,message.length());
      lcd.print(String1);
      lcd.setCursor(0,1);
      lcd.print(String2);
    }else{
      
    }
  
  }
}


  


