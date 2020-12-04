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
#include "../lib/MHAdapter/LiquidCrystal_I2C.h"
#include "../inc/productos.h"

using namespace vibration_dispenser;

control::State_machine machine_state;
io::Button disp_button(DISPENSE_BUTTON_PIN,100);
io::Button cancel_button(CANCEL_BUTTON_PIN,100);
io::Button up_button(UP_BUTTON_PIN,100);
io::Button right_button(RIGHT_BUTTON_PIN,100);
io::Button down_button(DOWN_BUTTON_PIN,100);
io::Button left_button(LEFT_BUTTON_PIN,100);
io::Button enter_button(ENTER_BUTTON_PIN,100);

HX711 scale;

#ifdef MODO_SERVO
Servo door_servo;
#endif

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Serial comm DEBUGGING
char incomingChar;

// Process variables
int weight=PESO_DEFAULT;
int read_weight;
int new_weight;
int progress=0;
int door_delay=TIEMPO_ESPERA*1000;
int relay_delay=TIEMPO_DE_RELAY*1000;
int delay_after_dispense=TIEMPO_DESPUES_DISP*1000;

int new_first_speed;
int new_second_speed;
int new_speed_change_percentage;
int speed;
int menu=0;
int product_id=PRODUCTO_INICIAL;
int new_product_id=PRODUCTO_INICIAL;
int first_speed=product_param[product_id][0];
int second_speed=product_param[product_id][1];
int speed_change_percentage=product_param[product_id][2];

// TODO: Refactor inside screencom class
// Forward definitions of Screencom
Key checkArrowButtons();
void resetArrowButtons();
void setScreen(Screen menu, int old_weight_=0, int new_weight_=0);
void splashScreen();
void standbyScreen();
void dispensingScreen();
void servedScreen();
void openDoorScreen();
void setWeightScreen(int old_weight_, int new_weight_, int col = 14);
void setSpeedScreen(int old_value_,int new_value_, int col = 14);
void changeConfirmedScreen();
void errorScreen(String msg);
int manageWeight(int saved_weight);
int manageSpeed(int saved_speed);
int manageProduct(int saved_product);
void setProductScreen();
void standbyMenus(int menu_num);

// Forward definitions of vibrator
void setVibration(int percentage);

void setup() {
  
  Serial.begin(115200);
  Serial.println("System initialized");
  
  #ifdef MODO_SERVO
  door_servo.attach(SERVO_PIN);
  door_servo.write(DOOR_CLOSED);
  #endif
  
  #ifdef MODO_MOTOR
  pinMode(DC_CCW_PIN,OUTPUT);
  pinMode(DC_CW_PIN,OUTPUT);
  #endif

  #ifdef MODO_MOTOR
  analogWrite(DC_CCW_PIN,VELOCIDAD_CIERRE);
  analogWrite(DC_CW_PIN,0);
  #endif

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  
  
  //if (scale.wait_ready_retry(20,100))  
  if (scale.is_ready())
  {    
    scale.set_scale(SCALE_GRAMS);
    scale.tare();
  }else{
    // This should be an Error condition
    Serial.println("Scale not detected");
  }
    
  // Screencom
  lcd.begin();
  setScreen(Screen::SPLASH);
  delay(500);
  machine_state.setState(control::State::STANDBY);
  setScreen(Screen::STANDBY);  
  
  // Vibrator
  pinMode(VIBRATOR_PIN, OUTPUT);

  // Relays
  pinMode(RELAY1_PIN,OUTPUT); // Vibrador para Tolva
  pinMode(RELAY2_PIN,OUTPUT); // Alarma
  pinMode(RELAY3_PIN,OUTPUT); // Chicharra
  pinMode(RELAY4_PIN,OUTPUT); // --Libre--

  digitalWrite(RELAY1_PIN,LOW);
  digitalWrite(RELAY2_PIN,LOW);
  digitalWrite(RELAY3_PIN,LOW);
  digitalWrite(RELAY4_PIN,LOW);

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
      cancel_button.update();
      
      if (cancel_button.getState())
      {
        cancel_button.reset();
        machine_state.setState(control::State::SERVED);
        lcd.clear();
        lcd.print("|  Vaciando... |");
      }
            

      //Menu scroller            
      switch (checkArrowButtons())
      {
      case Key::UP:
        resetArrowButtons();
        if (menu==6)
        {
          menu=0;
          standbyMenus(menu);
        }else
        {
          ++menu;
          standbyMenus(menu);                  
        }                
        break;
      case Key::DOWN:
        resetArrowButtons();
        if (menu==0)
        {
          menu=6;
          standbyMenus(menu);
        }else{
          --menu;
          standbyMenus(menu);        
        }
        break;
      
      case Key::SELECT:
        if (menu!=0)
        {
          switch (menu)
          {
          case 1:
            resetArrowButtons();
            machine_state.setState(control::State::TARE);
            Serial.println("State:= TARE");
            break;
          case 2:
            resetArrowButtons();
            machine_state.setState(control::State::SETGRAMS);
            Serial.println("State:= SETGRAMS");
            setScreen(Screen::SETWEIGHT,weight,weight);
            break;
          case 3:
            resetArrowButtons();
            machine_state.setState(control::State::SETSPEED1);
            Serial.println("State:= SETSPEED1");
            setScreen(Screen::SETSPEED1,first_speed,first_speed);
            break;
          case 4:
            resetArrowButtons();
            machine_state.setState(control::State::SETSPEED2);
            Serial.println("State:= SETSPEED2");
            setScreen(Screen::SETSPEED1,second_speed,second_speed);
            break;
          case 5:
            resetArrowButtons();
            machine_state.setState(control::State::SETSPEEDCHANGE);
            Serial.println("State:= SETSPEEDCHANGE");
            setScreen(Screen::SETSPEED1,speed_change_percentage,speed_change_percentage);
            break;
          case 6:
            resetArrowButtons();
            machine_state.setState(control::State::SETPRODUCT);
            Serial.println("State:= SETPRODUCT");
            setScreen(Screen::SETPRODUCT);
            break;
          
          default:
            break;
          }
        }        
        break;
      
      default:
        break;
      }
      
      if(incomingChar=='D' || disp_button.getState()){
        disp_button.reset();
        incomingChar='.';
        machine_state.setState(control::State::DISPENSING);        
        Serial.println("State:= DISPENSING"); 
        setScreen(Screen::DISPENSING);
        speed=first_speed;
        Serial.print("Speed:= ");
        Serial.println(speed);                            
      }     
      break;
    
    case control::State::TARE:      
      scale.tare();
      lcd.clear();
      lcd.print("| Bascula en 0 |");
      delay(1000);
      menu=0;
      standbyMenus(menu);
      machine_state.setState(control::State::STANDBY);
      Serial.println("State:= STANDBY");
      setScreen(Screen::STANDBY);
      break;
    
    case control::State::SETGRAMS:

      new_weight=manageWeight(weight);      
      if (new_weight!=weight)
      {
          weight=new_weight;
          changeConfirmedScreen();
          Serial.println(weight);
      }            
      machine_state.setState(control::State::STANDBY);
      Serial.println("State:= STANDBY");
      setScreen(Screen::STANDBY);
      menu=0;

      break;

    case control::State::SETSPEED1:
      
      new_first_speed=manageSpeed(first_speed);      
      if (new_first_speed!=first_speed)
      {
          first_speed=new_first_speed;          
          changeConfirmedScreen();
          Serial.println(first_speed);
      }

      menu=0;
      standbyMenus(menu);
      machine_state.setState(control::State::STANDBY);
      Serial.println("State:= STANDBY");
      setScreen(Screen::STANDBY);
      break;

    case control::State::SETSPEED2:
      
      new_second_speed=manageSpeed(second_speed);      
      if (new_second_speed!=second_speed)
      {
          second_speed=new_second_speed;          
          changeConfirmedScreen();
          Serial.println(second_speed);
      }
      
      menu=0;
      standbyMenus(menu);
      machine_state.setState(control::State::STANDBY);
      Serial.println("State:= STANDBY");
      setScreen(Screen::STANDBY);
      break;

    case control::State::SETSPEEDCHANGE:
      
      new_speed_change_percentage=manageSpeed(speed_change_percentage);      
      if (new_speed_change_percentage!=speed_change_percentage)
      {
          speed_change_percentage=new_speed_change_percentage;          
          changeConfirmedScreen();
          Serial.println(speed_change_percentage);
      }
      menu=0;
      standbyMenus(menu);
      machine_state.setState(control::State::STANDBY);
      Serial.println("State:= STANDBY");
      setScreen(Screen::STANDBY);
      break;
    
    case control::State::SETPRODUCT:
      
      new_product_id=manageProduct(product_id);      
      if (new_product_id!=product_id)
      {
          product_id=new_product_id;          
          first_speed=product_param[product_id][0];
          second_speed=product_param[product_id][1];
          speed_change_percentage=product_param[product_id][2];          
          changeConfirmedScreen();
          Serial.println(product_id);
      }
      
      menu=0;
      standbyMenus(menu);
      machine_state.setState(control::State::STANDBY);
      Serial.println("State:= STANDBY");
      setScreen(Screen::STANDBY);
      break;

    case control::State::DISPENSING:
      
      cancel_button.update();
      setVibration(speed);
      // TODO: Add "scale.is_ready() for protection and avoid hanging"
      if (scale.read() < 8000000)
      {        
        //Client reported scale was too sensible, averaging will help stabilize
        read_weight = scale.get_units(SENSIBILIDAD_DISPENSADO);                                         
        progress= (int)(((float)read_weight/weight)*100);        
        Serial.print("progreso: ");
        Serial.println(progress);
        
        if (progress>=speed_change_percentage || (weight<=100))
        {
          speed=second_speed;
          Serial.print("Speed:=");
          Serial.println(speed);
        }
        

      } else {
        speed=0;
        setVibration(speed);
        machine_state.setState(control::State::ERROR);
        Serial.println("State:= ERROR");
        errorScreen("Falla en bascula");        
        break;
      }
                  
      // TODO: Send to Screencom to update weight
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);      
      lcd.print(read_weight);
      lcd.print("/");
      lcd.print(weight);
      lcd.print("g");
      
      // Door button used as cancel
      if ((read_weight>=weight) || cancel_button.getState())      
      {        
        cancel_button.reset();
        speed=0;
        setVibration(speed);
        progress=0;        
        
        // Change: SERVED Screen now shows quantity dispensed
        setScreen(Screen::SERVED);
        Serial.println("State:= SERVED");

        // From here, we will delay 2s and jump right into FLUSH
        delay(delay_after_dispense);        
        
        digitalWrite(RELAY1_PIN,HIGH);        
        
        machine_state.setState(control::State::SERVED);        

      }
      break;  

    case control::State::SERVED:
        
        // In case we arrive here, jump to FLUSH        
        machine_state.setState(control::State::FLUSH);        
        #ifdef MODO_SERVO
        door_servo.write(DOOR_OPEN);      
        #endif

        #ifdef MODO_MOTOR
        analogWrite(DC_CCW_PIN,0);
        analogWrite(DC_CW_PIN,VELOCIDAD_APERTURA);
        #endif

        setScreen(Screen::OPENDOOR);
      break;

    case control::State::FLUSH:      
      cancel_button.update();
      read_weight = scale.get_units(SENSIBILIDAD_VACIADO);
      // Show weight as it falls down to 0
      // First erase bottom row
      lcd.setCursor(0,1);
      lcd.print("                ");
      // Show how weight comes down to 0
      lcd.setCursor(4,1);
      lcd.print(read_weight);
      lcd.print(" g");
      
      //For debug
      //if (incomingChar=='R' || cancel_button.getState())
      
      // we leave cancel_button enabled in case door gets stuck open
      if ((read_weight < 15) || cancel_button.getState())
      {        
        cancel_button.reset();
        delay(door_delay);
        
        
        digitalWrite(RELAY1_PIN,LOW);
        
        
        // Relevador para ALARMA
        digitalWrite(RELAY2_PIN,HIGH);
        delay(relay_delay);
        digitalWrite(RELAY2_PIN,LOW);
        

        machine_state.setState(control::State::STANDBY);        
        
        #ifdef MODO_SERVO
        door_servo.write(DOOR_CLOSED);
        #endif

        #ifdef MODO_MOTOR
        analogWrite(DC_CCW_PIN,VELOCIDAD_CIERRE);
        analogWrite(DC_CW_PIN,0);
        #endif
        
        setScreen(Screen::STANDBY);
        Serial.println("State:= STANDBY");
        menu=0;
      }
      
      break;

    default: //Unknown State, shouldn't be reachable. Must prompt error.
        //machine_state.setState(control::State::ERROR);
        if (checkArrowButtons()==Key::SELECT)
        {
          incomingChar='.';
          digitalWrite(RELAY1_PIN,LOW);
          resetArrowButtons();
          machine_state.setState(control::State::STANDBY);
          setScreen(Screen::STANDBY);
          break;
        }
              
      break;
    }  
}

//---------------------------------FUNCTIONS------------------------------------

Key checkArrowButtons(){
  
  up_button.update();
  right_button.update();
  left_button.update();
  down_button.update();
  enter_button.update();

  if(up_button.getState()==true){
    return Key::UP;
  }
  if(right_button.getState()==true){
    return Key::RIGHT;
  }
  if(left_button.getState()==true){
    return Key::LEFT;
  }
  if(down_button.getState()==true){
    return Key::DOWN;
  }
  if(enter_button.getState()==true){
    return Key::SELECT;
  } 
  return Key::NO_KEY;

}

void resetArrowButtons(){
  up_button.reset();
  right_button.reset();
  left_button.reset();
  down_button.reset();
  enter_button.reset();
}

void setScreen(Screen menu, int old_value_, int new_value_){
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
  
  case Screen::SETSPEED1:
    setSpeedScreen(old_value_,new_value_);    
  break;
  
  case Screen::SETWEIGHT:
    setWeightScreen(old_value_,new_value_);
    break;
  case Screen::SETPRODUCT:
    setProductScreen();
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
    //errorScreen();
    break;
  
  default:
    break;
  }
  
}  
void splashScreen(){
  lcd.clear();    
  lcd.setCursor(0,0);  
  lcd.print("Sistema iniciado");
  lcd.setCursor(11,1);
  lcd.print("V1.0");
  delay(500);
  lcd.clear();    
  lcd.setCursor(0,0);  
  lcd.print("|-----IDEA-----|");
  lcd.setCursor(0,1);
  lcd.print("|              |");
  delay(2000);

}
void standbyScreen(){  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Oprima 1 para  ");
  lcd.setCursor(0,1);
  lcd.print(" surtir ");
  lcd.print(weight);
  lcd.print("g");
}
void dispensingScreen(){
  lcd.clear();
  lcd.print("Dispensando...");
}
void servedScreen(){
  lcd.clear();
  lcd.print("   Dispensado   ");   
  // screen mockup:
  // |   Dispensado   |
  // |     1000 g     |
  lcd.setCursor(4,1);
  lcd.print(scale.get_units(SENSIBILIDAD_VACIADO));
  lcd.print(" g");
}
void openDoorScreen(){
  lcd.clear();
  // Only print static text on first row  
  lcd.print("   Vaciando...  "); 
}
void setWeightScreen(int old_weight_, int new_weight_, int col){
  lcd.clear();
  lcd.print("Peso prog.");
  lcd.setCursor(0,1);
  lcd.print("Nuevo peso");
  lcd.setCursor(15,0);
  lcd.print("g");
  lcd.setCursor(15,1);
  lcd.print("g");
  
  if (new_weight_<10)
  {        
    lcd.setCursor(14,1);
  }else if(new_weight_<100){    
    lcd.setCursor(13,1);
  }else if (new_weight_<1000){
    lcd.setCursor(12,1);
  } else {
    lcd.setCursor(11,1);
  }
  lcd.print(new_weight_);
  

  if (old_weight_<10)
  {        
    lcd.setCursor(14,0);
  }else if(old_weight_<100){    
    lcd.setCursor(13,0);
  }else if (old_weight_<1000){
    lcd.setCursor(12,0);
  } else {
    lcd.setCursor(11,0);
  }
  lcd.print(old_weight_);
  
  lcd.setCursor(col,1);
  lcd.blink();
}

// TODO: Change to Speed
void setSpeedScreen(int old_speed_, int new_speed_, int col){
  lcd.clear();
  lcd.print("Vel prog.");
  lcd.setCursor(0,1);
  lcd.print("Nueva Vel");
  
  if (new_speed_<10)
  {        
    lcd.setCursor(14,1);
  }else if(new_speed_<100){    
    lcd.setCursor(13,1);
  }else if (new_speed_<1000){
    lcd.setCursor(12,1);
  } else {
    lcd.setCursor(11,1);
  }
  lcd.print(new_speed_);
  

  if (old_speed_<10)
  {        
    lcd.setCursor(14,0);
  }else if(old_speed_<100){    
    lcd.setCursor(13,0);
  }else if (old_speed_<1000){
    lcd.setCursor(12,0);
  } else {
    lcd.setCursor(11,0);
  }
  lcd.print(old_speed_);
  
  lcd.setCursor(col,1);
  lcd.blink();
}



// Manages weight change screen. Allows user to change desired weight digit by
// digit.
int manageWeight(int saved_weight){
    
    int set_weight=saved_weight;
    int col=14;
    int increments[4] = {1,10,100,1000};    
    
    while (checkArrowButtons()!=Key::SELECT)
    {
        switch (checkArrowButtons())
        {
        case Key::RIGHT:              
            resetArrowButtons();                    
                if (col<14)
                {            
                    ++col;
                    lcd.setCursor(col,1);
                }        
            break;
        case Key::UP:              
            resetArrowButtons();        
            Serial.println("UP");
            set_weight += increments[14-col];
            if (set_weight>=2000)
            {
                set_weight=2000;
            }                        
            setWeightScreen(saved_weight,set_weight,col);
            break;
        case Key::DOWN:              
            resetArrowButtons();        
            Serial.println("DOWN");
            set_weight -= increments[14-col];
            if (set_weight<=0)
            {
                set_weight=0;
            }                        
            setWeightScreen(saved_weight,set_weight,col);
            break;
        case Key::LEFT:        
            resetArrowButtons();                            
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
    resetArrowButtons();
    return set_weight;       
}
// Manages speed change screen. Allows user to change desired weight digit by
// digit.
int manageSpeed(int saved_speed){
    
    int set_speed=saved_speed;
    int col=14;
    int increments[3] = {1,10,100};    
    
    while (checkArrowButtons()!=Key::SELECT)
    {
        switch (checkArrowButtons())
        {
        case Key::RIGHT:              
            resetArrowButtons();                    
                if (col<14)
                {            
                    ++col;
                    lcd.setCursor(col,1);
                }        
            break;
        case Key::UP:              
            resetArrowButtons();        
            Serial.println("UP");
            set_speed += increments[14-col];
            if (set_speed>=255)
            {
                set_speed=255;
            }                        
            setSpeedScreen(saved_speed,set_speed,col);
            break;
        case Key::DOWN:              
            resetArrowButtons();        
            Serial.println("DOWN");
            set_speed -= increments[14-col];
            if (set_speed<=0)
            {
                set_speed=0;
            }                        
            setSpeedScreen(saved_speed,set_speed,col);
            break;
        case Key::LEFT:        
            resetArrowButtons();                            
                if (col>12)
                {            
                    --col;
                    lcd.setCursor(col,1);
                }
            break;        
        
        default:        
            break;
            }    
        }
    resetArrowButtons();
    return set_speed;       
}

void setProductScreen(){
  lcd.clear();
  lcd.print("Selec. producto");
}

// Manages product selection menu
int manageProduct(int saved_product){
    
    int set_product=saved_product;
    char product_to_show[16];

    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);                        
                             
    for (size_t i = 0; i < 16; i++)
    {
      product_to_show[i]=product_name[set_product][i];
    }            
    lcd.print(product_to_show);
  
    while (checkArrowButtons()!=Key::SELECT)
    {
        switch (checkArrowButtons())
        {
        
        case Key::UP:              
            resetArrowButtons();
            if (set_product==NUM_PRODUCTOS-1)
            {
              set_product=0;
            }else{
              set_product++;
            }
            lcd.setCursor(0,1);
            lcd.print("                ");
            lcd.setCursor(0,1);                        
                             
            for (size_t i = 0; i < 16; i++)
            {
              product_to_show[i]=product_name[set_product][i];
            }            
            lcd.print(product_to_show);
            
            break;
        case Key::DOWN:              
            resetArrowButtons();
            if (set_product==0)
            {
              set_product=NUM_PRODUCTOS-1;
            }else{
              set_product--;
            }
            lcd.setCursor(0,1);
            lcd.print("                ");
            lcd.setCursor(0,1);                        
            
            for (size_t i = 0; i < 16; i++)
            {
              product_to_show[i]=product_name[set_product][i];
            }            
            lcd.print(product_to_show);

            break;
        default:        
            break;
            }    
        }
    resetArrowButtons();
    return set_product;       
}

void changeConfirmedScreen(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("|Valor cambiado|");
    lcd.setCursor(0,1);
    lcd.print("| exitosamente |");
    delay(1500);
}

void standbyMenus(int menu_num){
  lcd.clear();
  switch (menu_num)
  {
  case 0:
    //STANDBY
    standbyScreen();
    break;  
  case 1:
    //TARE
    lcd.print("Presione  SELECT");
    lcd.setCursor(0,1);
    lcd.print("    para  tarear");
    break;
  case 2:
    //SETGRAMS
    lcd.print("Presione  SELECT");
    lcd.setCursor(0,1);
    lcd.print("  config  peso");
    break;
  case 3:
    //SETSPEED1
    lcd.print("Presione  SELECT");
    lcd.setCursor(0,1);
    lcd.print("Config  vel. uno");
    break;
  case 4:
    //SETSPEED2
    lcd.print("Presione  SELECT");
    lcd.setCursor(0,1);
    lcd.print("Config  vel. dos");
    break;
  case 5:
    //SETSPEEDCHANGE
    lcd.print("Presione  SELECT");
    lcd.setCursor(0,1);
    lcd.print(" % p. cambio vel");
    break;
  
  case 6:
    //SETPRODUCT
    lcd.print("Presione  SELECT");
    lcd.setCursor(0,1);
    lcd.print("Selec.  Producto");
    break;
  
  default:
    break;
  }
}

void setVibration(int percentage){
  //int pwm=map(percentage,0,100,0,255);
  //analogWrite(VIBRATOR_PIN,pwm);
  analogWrite(VIBRATOR_PIN,percentage);
}

void errorScreen(String msg){
  //TO DO: Define Error codes and screen
  lcd.clear();
  lcd.print(msg);
  lcd.setCursor(0,1);
  lcd.print("Presione Select");
}

//------------------------------END OF PROGRAM----------------------------------