#include "IMUAccess.h"
#include "Arduino.h"
#include "Wire.h"

IMUAccessTwo IMUAccess;


bool IMUAccessTwo::setupADXL345(void)
{

	//Writes a a 00101000 to the Power control bit
	//Turns accelerometer into Measurement mode and disables autosleep
	Wire.beginTransmission(ADXL345_ADDRESS);
	Wire.write(ADXL345_POWER_CTL);
	Wire.write(40);
	Wire.endTransmission(true);

	Serial.print(" Accelerometer Ready");
	Serial.print("\n");
}
bool IMUAccessTwo::setupL3G4200D(void)
{
}
bool IMUAccessTwo::setupHMC5883L(void)
{
	Serial.print("Compass Ready\n");
	Wire.beginTransmission(HMC5883L_ADDRESS);
	Wire.write(HMC5883L_MODE);
	Wire.write(0);
	Wire.endTransmission(true);

}
int IMUAccessTwo::getAccelData()
{
	Wire.beginTransmission(ADXL345_ADDRESS);
    Wire.write(ADXL345_DATA_X0);              //Initial data position order is XZY, NOT XYZ
    int successfulTransmission = Wire.endTransmission();
    if(successfulTransmission != 0)
    {
      Serial.print("read failure on: ");
      Serial.print(ADXL345_ADDRESS);
      Serial.print("due to endTransmission = ");
      Serial.print(successfulTransmission);
      Wire.endTransmission(true);
	  return 300;
    }
	else
    {
      Serial.print("got an Accelerometer value:\n");
      Wire.requestFrom(ADXL345_ADDRESS, 6); // read 6 bytes
	  int XMSB = Wire.read();
	  int XLSB = Wire.read();
	  int YMSB = Wire.read();
	  int YLSB = Wire.read();
	  int ZMSB = Wire.read();
	  int ZLSB = Wire.read();

      Serial.print("("); Serial.print(XMSB); Serial.print(", "); Serial.print(XLSB); Serial.print(")\n");
	  Serial.print("("); Serial.print(YMSB); Serial.print(", "); Serial.print(YLSB); Serial.print(")\n");
	  Serial.print("("); Serial.print(ZMSB); Serial.print(", "); Serial.print(ZLSB); Serial.print(")\n");
      Wire.endTransmission(true);
      //Serial.print(Wire.available());
    }
    Serial.print("\n");
}
int IMUAccessTwo::getGyroData()
{
}
int IMUAccessTwo::getCompassData()
{
	Wire.beginTransmission(HMC5883L_ADDRESS);
    Wire.write(HMC5883L_DATA_X0);              //Initial data position order is XZY, NOT XYZ
    int successfulTransmission = Wire.endTransmission();
    if(successfulTransmission != 0)
    {
      Serial.print("read failure on: ");
      Serial.print(HMC5883L_ADDRESS);
      Serial.print("due to endTransmission = ");
      Serial.print(successfulTransmission);
      Wire.endTransmission(true);
	  return 300;
    }
    else
    {
      Serial.print("got a Compass value:\n");
      Wire.requestFrom(HMC5883L_ADDRESS, 6); // read 6 bytes
	  int XMSB = Wire.read();
	  int XLSB = Wire.read();
	  int YMSB = Wire.read();
	  int YLSB = Wire.read();
	  int ZMSB = Wire.read();
	  int ZLSB = Wire.read();

      Serial.print("("); Serial.print(XMSB); Serial.print(", "); Serial.print(XLSB); Serial.print(")\n");
	  Serial.print("("); Serial.print(YMSB); Serial.print(", "); Serial.print(YLSB); Serial.print(")\n");
	  Serial.print("("); Serial.print(ZMSB); Serial.print(", "); Serial.print(ZLSB); Serial.print(")\n");
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
