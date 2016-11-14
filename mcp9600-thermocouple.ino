// This #include statement was automatically added by the Particle IDE.
#include "K-Type-9600-Thermocouple.h"

ThermoCouple tempSens;

void setup() {
    int a = tempSens.discover();
    tempSens.init(a);
}

void loop() {
    Serial.printf("Temperature = %f \n", tempSens.readTemp());
    delay(500);
}