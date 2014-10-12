#include "IMUAccess.h"
#include "Arduino.h"
#include "Wire.h"



bool IMUAccessTwo::setupADXL345()
{
}
bool IMUAccessTwo::setupL3G4200D()
{
}
bool IMUAccessTwo::setupHMC5883L()
{
  Wire.beginTransmission(HMC5883L_ADDRESS);
  Wire.write(HMC5883L_MODE);
  Wire.write(0);
  int value = Wire.endTransmission();
  Serial.print(value);
  //delay(100);
}

bool setupHMC5883L()
{
}
