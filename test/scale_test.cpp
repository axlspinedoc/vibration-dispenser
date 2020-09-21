#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 52;
const int LOADCELL_SCK_PIN = 53;
long initial_sample;
float scale_factor;

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
  initial_sample=scale.get_units(10);
  
  scale_factor=initial_sample/710;
  Serial.print("Scale= ");
  Serial.println(scale_factor);  
  
  
  scale.set_scale(scale_factor);
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