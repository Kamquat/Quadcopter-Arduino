#include "IMUAccess.h"
#include "Arduino.h"
#include "Wire.h"
#include "Config.h"

IMUAccessTwo IMUAccess;


bool IMUAccessTwo::setupADXL345(void)
{

	//Writes a a 00101000 to the Power control bit
	//Turns accelerometer into Measurement mode and disables autosleep
	
	while(Wire.available()); //This ensures the wire is clear before executing
	
	Wire.beginTransmission(ADXL345_ADDRESS);
	Wire.write(ADXL345_POWER_CTL);
	Wire.write(40);
	Wire.endTransmission(true);
	
	while(Wire.available()); //This ensures the wire is clear before executing
	
	Wire.beginTransmission(ADXL345_ADDRESS);
	Wire.write(ADXL345_DATA_FORMAT);
	Wire.write(33);
	Wire.endTransmission(true);
	if(DEBUG == true)
	{
		Serial.print(" Accelerometer Ready");
		Serial.print("\n");
	}
}
bool IMUAccessTwo::setupL3G4200D(void)
{
}
bool IMUAccessTwo::setupHMC5883L(void)
{
	if(DEBUG == true)
	{
		Serial.print("Compass Ready\n");
	}
	while(Wire.available()); //This ensures the wire is clear before executing
	
	Wire.beginTransmission(HMC5883L_ADDRESS);
	Wire.write(HMC5883L_MODE);
	Wire.write(0);
	Wire.endTransmission(true);

}
int IMUAccessTwo::getAccelData()
{
	while(Wire.available()); //This ensures the wire is clear before executing

	Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(ADXL345_DATA);              //Initial data position order is XZY, NOT XYZ
    int successfulTransmission = Wire.endTransmission();
	
    if(successfulTransmission != 0)
    {
		if(DEBUG == true)
		{
		Serial.print("read failure on: ");
		Serial.print(ADXL345_ADDRESS);
		Serial.print("due to endTransmission = ");
		Serial.print(successfulTransmission);
		}
      Wire.endTransmission(true);
	  
	  return 300;
    }
	else
    {
		if(DEBUG == true)
		{
			Serial.print("got an Accelerometer value:\n");
		}
		Wire.requestFrom(ADXL345_ADDRESS, 6); // read 6 bytes
		while(Wire.available() < 6);
		int XLSB = Wire.read();
		int XMSB = Wire.read();
		int YLSB = Wire.read();
		int YMSB = Wire.read();
		int ZLSB = Wire.read();
		int ZMSB = Wire.read();
		
		
		if(DEBUG == true)
		{
			Serial.print("("); Serial.print(XMSB); Serial.print(", "); Serial.print(XLSB); Serial.print(")\n");
			Serial.print("("); Serial.print(YMSB); Serial.print(", "); Serial.print(YLSB); Serial.print(")\n");
			Serial.print("("); Serial.print(ZMSB); Serial.print(", "); Serial.print(ZLSB); Serial.print(")\n");
			Serial.print("\n");
		}
	  Wire.endTransmission(true);
    }
}
int IMUAccessTwo::getGyroData()
{
}
int IMUAccessTwo::getCompassData()
{
	//while(Wire.available()); //This ensures the wire is clear before executing

	Wire.beginTransmission(HMC5883L_ADDRESS);
    Wire.write(HMC5883L_DATA);              //Initial data position order is XZY, NOT XYZ
    int successfulTransmission = Wire.endTransmission();
    if(successfulTransmission != 0)
    {
		if(DEBUG == true)
		{
			Serial.print("read failure on: ");
			Serial.print(HMC5883L_ADDRESS);
			Serial.print("due to endTransmission = ");
			Serial.print(successfulTransmission);
			Serial.print("\n");
		}
      Wire.endTransmission(true);
	  return 300;
    }
    else
    {
		if(DEBUG == true)
		{
		Serial.print("got a Compass value:\n");
		}
		
		Wire.requestFrom(HMC5883L_ADDRESS, 6); // read 6 bytes
		
		while(Wire.available() < 6);
		
		int XMSB = Wire.read();
		int XLSB = Wire.read();
		int YMSB = Wire.read();
		int YLSB = Wire.read();
		int ZMSB = Wire.read();
		int ZLSB = Wire.read();
		
		if(DEBUG == true)
		{
			Serial.print("("); Serial.print(XMSB); Serial.print(", "); Serial.print(XLSB); Serial.print(")\n");
			Serial.print("("); Serial.print(YMSB); Serial.print(", "); Serial.print(YLSB); Serial.print(")\n");
			Serial.print("("); Serial.print(ZMSB); Serial.print(", "); Serial.print(ZLSB); Serial.print(")\n");
			Serial.print("\n");
		}
		Wire.endTransmission(true);
      //Serial.print(Wire.available());
    }
}
extern bool setupHMC5883L(void)
{
	Serial.print("Also Here");
}
//extern IMUAccessTwo IMUAccess;
