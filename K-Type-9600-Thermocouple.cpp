#include "K-Type-9600-Thermocouple.h"

bool ThermoCouple::init(int addr){
    address = addr;
    if ( !Wire.isEnabled() ) {
        Wire.setSpeed(i2cClockSpeed);
        Wire.begin();
    }
    if(temrmo_set() && device_set()){
        return true;
    }
}

int ThermoCouple::discover(){
    if ( !Wire.isEnabled() ) {
        Wire.setSpeed(i2cClockSpeed);
        Wire.begin();
    }
    for(int i = 96; i < 104; i++){
        Wire.beginTransmission(i);
        status = Wire.endTransmission();
        if(status == 0){
            address = i;
            return i;
        }
    }
    return error;
}

float ThermoCouple::readTemp(){
    if ( !Wire.isEnabled() ) {
        Wire.setSpeed(i2cClockSpeed);
        Wire.begin();
    }
    Wire.beginTransmission(address);
    Wire.write(0x00);
    status = Wire.endTransmission();
    if(status != 0){
        return error;
    }
    Wire.requestFrom(address, 2);
    startTime = millis();
    while(Wire.available() < 2 && millis() < startTime+readTimeout);
    if(Wire.available() < 2){
        return error;
    }
    float temp;
    data[0] = Wire.read();
    data[1] = Wire.read();
    Serial.printf("Data[0] = %i, Data[1] = %i \n", data[0], data[1]);
    if((data[0] & 0x80) == 0x80){
        data[0] = data[0] & 0x7F;
        temp = 1024 - (data[0] *16.00 + data[1]/16.00);
        if(fahrenheit){
            temp = (temp *1.8)+32;
        }
        return temp;
    }
    temp = data[0]*16.00+data[1]/16.00;
    if(fahrenheit){
        temp = (temp *1.8)+32;
    }
    return temp;
}

bool ThermoCouple::temrmo_set()
{
    Wire.beginTransmission(address);
    Wire.write(0x05);
    Wire.write(0x00);
    byte status = Wire.endTransmission();
    if(status == 0){
        return true;
    }else{
        return false;
    }
}
////////////// this function can be used to set the device config
bool ThermoCouple::device_set()
{
    Wire.beginTransmission(address);
    Wire.write(0x06);
    Wire.write(0x00);
    byte status = Wire.endTransmission();
    if(status == 0){
        return true;
    }else{
        return false;
    }
}
