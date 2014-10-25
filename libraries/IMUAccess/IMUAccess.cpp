#include "IMUAccess.h"
#include "Arduino.h"
#include "Wire.h"
#include "Config.h"

IMUAccessTwo IMUAccess;
	int currentAccelValues[3] = {0};
	int currentCompassValues[3] = {0};
	int currentGyroValues[3] = {0};
bool IMUAccessTwo::setupDevices(void)
{
	setupADXL345();   	//Accelerometer
	setupHMC5883L(); 	//Compass
	setupL3G4200D(); 	//Gyroscopes	
	setupBMP085();		//Barometer

}
void IMUAccessTwo::updateIMUValues(void)
{
	getAccelData(currentAccelValues);
	getCompassData(currentCompassValues);
	getGyroData(currentGyroValues);
	
	if(DEBUG == true)
	{
	Serial.print(Serial.print(currentAccelValues[1]));
	Serial.print("\n\n\n");
	/*
		Serial.print("Accelerometer Values\n");
    
		Serial.print("("); Serial.print(currentAccelValues[1]); Serial.print(", "); Serial.print(currentAccelValues[0]); Serial.print(")\n");
		Serial.print("("); Serial.print(currentAccelValues[3]); Serial.print(", "); Serial.print(currentAccelValues[2]); Serial.print(")\n");
		Serial.print("("); Serial.print(currentAccelValues[5]); Serial.print(", "); Serial.print(currentAccelValues[4]); Serial.print(")\n");
		Serial.print("\n");
    
		Serial.print("Compass Values\n");
    
		Serial.print("("); Serial.print(currentCompassValues[1]); Serial.print(", "); Serial.print(currentCompassValues[0]); Serial.print(")\n");
		Serial.print("("); Serial.print(currentCompassValues[3]); Serial.print(", "); Serial.print(currentCompassValues[2]); Serial.print(")\n");
		Serial.print("("); Serial.print(currentCompassValues[5]); Serial.print(", "); Serial.print(currentCompassValues[4]); Serial.print(")\n");
		Serial.print("\n");
		*/
    
	}
	if (DEBUG_TIMING == true)
	{
	static int maxCount = 100;
	static int iterationCount = 0;
	static int myTime = 0;
	static int previousMicros = 0;
		iterationCount++;
		if (iterationCount == maxCount)
		{
			myTime = micros() - previousMicros;
			//myTime /= 1000000;
			Serial.print(maxCount);
			Serial.print(" rounds took: ");
			Serial.print(myTime);
			Serial.print(" micro-seconds \n");

			iterationCount = 0;
			delay(5000);
			previousMicros = micros();
		}
	}
}
bool IMUAccessTwo::setupADXL345(void)
{
	int dataFormatValue = 32 + ACCEL_RESOLUTION; //allows g setting to be enabled in config

	
	while(Wire.available()); //This ensures the wire is clear before executing
	
	//Writes a a 00101000 to the Power control bit
	//Turns accelerometer into Measurement mode and disables autosleep
	Wire.beginTransmission(ADXL345_ADDRESS);
	Wire.write(ADXL345_POWER_CTL);
	Wire.write(40);
	Wire.endTransmission(true);
	
	while(Wire.available()); //This ensures the wire is clear before executing
	
	
	//writes a 32 + ACCEL_RESOLUTION
	//sets g range, right justifies data and enables full resolution
	Wire.beginTransmission(ADXL345_ADDRESS);
	Wire.write(ADXL345_DATA_FORMAT);
	
	Wire.write(dataFormatValue);
	Wire.endTransmission(true);
	
	while(Wire.available()); //This ensures the wire is clear before executing
	
	
	//Disables all extra settings on accelerometer
	//will change as new options are added
	Wire.beginTransmission(ADXL345_ADDRESS);
	Wire.write(ADXL345_INT_ENABLE);
	
	Wire.write(0);
	Wire.endTransmission(true);
	
	if(DEBUG == true)
	{
		Serial.print(" Accelerometer Ready");
		Serial.print("\n");
	}
	
	return true;
}
bool IMUAccessTwo::setupL3G4200D(void)
{
	while(Wire.available()); //This ensures the wire is clear before executing
	
	//
	//
	Wire.beginTransmission(L3G4200D_ADDRESS);
	Wire.write(L3G4200D_CTRL_REG1);
	Wire.write(255);           //sets to fastes requency, highest cut-off and enables all axis
	Wire.endTransmission(true);
	
	while(Wire.available()); //This ensures the wire is clear before executing
	
	Wire.beginTransmission(L3G4200D_ADDRESS);
	Wire.write(L3G4200D_CTRL_REG4);
	
	int ctrlReg4Value = GYRO_DATA_RATE * 16;
	
	Wire.write(ctrlReg4Value);           //sets to frequency in config, highest cut-off and enables all axis
	Wire.endTransmission(true);
	
	return true;
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
	return true;

}
bool IMUAccessTwo::setupBMP085(void)
{
}
void IMUAccessTwo::getAccelData(int newAccelValues[])
{
	readIMU(ADXL345_ADDRESS,ADXL345_DATA, newAccelValues);
	/*
	byte incomingValues[6];

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
	 
    }
	else
    {
		Wire.requestFrom(ADXL345_ADDRESS, 6); // read 6 bytes
		while(Wire.available() < 6);
		for(byte i = 0; i <6; i++)
		{
			incomingValues[i] = Wire.read();
		}
		newAccelValues[0] = incomingValues[1]<<8 | incomingValues[0];
		newAccelValues[1] = incomingValues[3]<<8 | incomingValues[2];
		newAccelValues[2] = incomingValues[5]<<8 | incomingValues[4];
		
		
	  Wire.endTransmission(true);
    }*/
}
void IMUAccessTwo::getGyroData(int newGyroValues[])
{
	//readIMU(L3G4200D_ADDRESS,L3G4200D_DATA, newGyroValues);
	/*
	Wire.beginTransmission(L3G4200D_ADDRESS);
	Wire.write(L3G4200D_DATA);
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
    }*/
}
void IMUAccessTwo::getCompassData(int newCompassValues[])
{
	readIMU(HMC5883L_ADDRESS,HMC5883L_DATA, newCompassValues);
/*
	byte incomingValues[6] = {0};
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
    }
    else
    {
		Wire.requestFrom(HMC5883L_ADDRESS, 6); // read 6 bytes
		
		while(Wire.available() < 6);
		
		for(byte i = 0; i < 6; i++)
		{
			incomingValues[i] = Wire.read();
		}
				
		newCompassValues[0] = incomingValues[1]<<8 | incomingValues[0];
		newCompassValues[1] = incomingValues[3]<<8 | incomingValues[2];
		newCompassValues[2] = incomingValues[5]<<8 | incomingValues[4];
		
		Wire.endTransmission(true);
      //Serial.print(Wire.available());
    }
	*/
}
void IMUAccessTwo::readIMU(int deviceAddress, int dataAddress, int newValues[])
{
	byte incomingValues[6] = {0};
	while(Wire.available()); //This ensures the wire is clear before executing

	Wire.beginTransmission(deviceAddress);
    Wire.write(dataAddress);              //Initial data position order is XZY, NOT XYZ
    int successfulTransmission = Wire.endTransmission();
	
    if(successfulTransmission != 0)
    {
		if(DEBUG == true)
		{
			Serial.print("read failure on: ");
			Serial.print(deviceAddress);
			Serial.print("due to endTransmission = ");
			Serial.print(successfulTransmission);
			Serial.print("\n");
		}
      Wire.endTransmission(true);
    }
    else
    {
		Wire.requestFrom(deviceAddress, 6); // read 6 bytes
		
		while(Wire.available() < 6);
		
		for(byte i = 0; i < 6; i++)
		{
			incomingValues[i] = Wire.read();
		}
				
		newValues[0] = incomingValues[1]<<8 | incomingValues[0];
		newValues[1] = incomingValues[3]<<8 | incomingValues[2];
		newValues[2] = incomingValues[5]<<8 | incomingValues[4];
		
		Wire.endTransmission(true);
      //Serial.print(Wire.available());
    }
}