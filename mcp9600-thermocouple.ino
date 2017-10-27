// This #include statement was automatically added by the Particle IDE.
#include "K-Type-9600-Thermocouple.h"

ThermoCouple tempSens;
String temperature;

void setup() {
    int a = tempSens.discover();
    if(tempSens.init(a)){
        Serial.println("Thermocouple init success");
    }else{
        Serial.println("Thermocouple init failed");
    }
    Particle.variable("Temperature", temperature);
}

void loop() {
    temperature = String(tempSens.readTemp());
    Serial.print("Temperature = "+temperature);
    delay(500);
}
