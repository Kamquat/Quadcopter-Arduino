#include "IMUAccess.h"
#include "Arduino.h"
#include "Wire.h"


IMUAccessTwo::IMUAccessTwo()
{
}
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

extern bool setupHMC5883L()
{
}
extern IMUAccessTwo IMUAccess = new IMUAccessTwo();
