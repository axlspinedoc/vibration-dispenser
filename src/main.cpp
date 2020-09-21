 
#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 52;
const int LOADCELL_SCK_PIN = 53;
long first_read;
float SCALE;
float OFFSET;

HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
  Serial.println("Load cell initialized");
  delay(1000);

  Serial.println("Place known weight");
  delay(8000);  
  first_read=scale.get_units(10);
  
  SCALE=first_read/710;
  Serial.print("Scale= ");
  Serial.println(SCALE);  
  
  
  scale.set_scale(SCALE);
  delay(5000);
  
}

void loop() {    
  
  if (scale.wait_ready_timeout(1000)) {
    long reading = scale.get_units();
    Serial.print("HX711 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }

  delay(200);
  
}