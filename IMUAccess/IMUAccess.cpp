#include "IMUAccess.h"
#include "Arduino.h"
#include "Wire.h"

IMUAccessTwo IMUAccess;


bool IMUAccessTwo::setupADXL345(void)
{
}
bool IMUAccessTwo::setupL3G4200D(void)
{
}
bool IMUAccessTwo::setupHMC5883L(void)
{
	Serial.print("HAPPY");
}

int IMUAccessTwo::retrieveValue(int address, int secondAddress)
{
	Wire.beginTransmission(address);
    Wire.write(secondAddress); // register to read
    int value = Wire.endTransmission();
    if(value != 0)
    {
      Serial.print("failure on: ");
      Serial.print(secondAddress);
      Serial.print("due to endTransmission = ");
      Serial.print(value);
      Wire.endTransmission(true);
    }
    else
    {
      Serial.print("got a value:   ");
      Serial.print(secondAddress);
      Serial.print(" = ");
      Wire.requestFrom(address, 1); // read a byte
      Serial.print(Wire.read());
      Wire.endTransmission(true);
      //Serial.print(Wire.available());
    }
    Serial.print("\n");
}

extern bool setupHMC5883L(void)
{
	Serial.print("Also Here");
}
//extern IMUAccessTwo IMUAccess;
