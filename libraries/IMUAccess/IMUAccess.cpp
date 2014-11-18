/*
Compass and Barometer not yet ready
*/
#include "IMUAccess.h"
#include "Arduino.h"
#include "Wire.h"
#include "Config.h"
	
bool IMUAccessTwo::setupDevices(void)
{
	accelMicros = 0, gyroMicros = 0, compassMicros = 0;
	accelInterval = 0, gyroInterval = 0, compassInterval = 0;
	gyroOffsets[3] = {0};
	//currentAccelValues[3] = {0};
	//currentCompassValues[3] = {0};
	//currentGyroValues[3] = {0};
	//Sets
	switch(ACCEL_FREQUENCY)
	{
		case 13: 	accelInterval = 1000000/800;
					break;
		case 12:	accelInterval = 1000000/400;
					break;
		case 11:	accelInterval = 1000000/200;
					break;
		case 10:	accelInterval = 1000000/100;
					break;
		case 9:		accelInterval = 1000000/50;
					break;
	}
	switch(GYRO_FREQUENCY)
	{
		case 0: 	gyroInterval = 1000000/100;
					break;
		case 1:		gyroInterval = 1000000/200;
					break;
		case 2:		gyroInterval = 1000000/400;
					break;
		case 3:		gyroInterval = 1000000/800;
	}
	switch(COMPASS_FREQUENCY)
	{
		case 3: 	compassInterval = 1000000/7.5;
					break;
		case 4:		compassInterval = 1000000/15;
					break;
		case 5:		compassInterval = 1000000/30;
					break;
		case 6:		compassInterval = 1000000/75;
	}

	setupADXL345();   	//Accelerometer
	setupL3G4200D(); 	//Gyroscopes
	setupHMC5883L(); 	//Compass	
	setupBMP085();		//Barometer
	
	if(DEBUG == true)
	{
		Serial.print("IMU Ready\n");
	}


}
void IMUAccessTwo::updateIMUValues(void)
{
	//currently the new values not being passed up to this level
	if(micros()-accelMicros > accelInterval)  //Accesses Accelerometer at frequency from Config
	{
		bool goodAccelRead = getAccelData();
		if(goodAccelRead ==true) {accelMicros = micros();}
	}
	if(micros()-gyroMicros > gyroInterval)     //Accesses Gyros at frequency from Config
	{
		bool goodGyroRead = getGyroData();
		if(goodGyroRead == true) {gyroMicros = micros();}
	}
	if(micros()-compassMicros > compassInterval)  //Accesses Compass at frequency from Config
	{	
		bool goodCompassRead = getCompassData();
		if(goodCompassRead == true) {compassMicros = micros();}
	}
}
bool IMUAccessTwo::setupADXL345(void)
{
	int dataFormatValue = 32 + ACCEL_RESOLUTION; //allows g setting to be enabled in config

	//Writes a a 00101000 to the Power control bit
	//Turns accelerometer into Measurement mode and disables autosleep
	
	//the extra Whiles ensure the write is successful
	while(Wire.available()); //This ensures the wire is clear before executing
	while((writeIMU(ADXL345_ADDRESS,ADXL345_POWER_CTL,40)));
	
	
	//sets accelerometer to value set in ACCEL_FREQUENCY, 800Hz-100Hz
	while(Wire.available()); //This ensures the wire is clear before executing
	while((writeIMU(ADXL345_ADDRESS,ADXL345_DATA_RATE,ACCEL_FREQUENCY)));
	
	
	//writes a 32 + ACCEL_RESOLUTION
	//sets g range, right justifies data and enables full resolution
	while(Wire.available()); //This ensures the wire is clear before executing
	while((writeIMU(ADXL345_ADDRESS,ADXL345_DATA_FORMAT,dataFormatValue)));
	
	
	//Disables all extra settings on accelerometer
	//will change as new options are added
	while(Wire.available()); //This ensures the wire is clear before executing
	while((writeIMU(ADXL345_ADDRESS,ADXL345_INT_ENABLE,0)));
	
	if(DEBUG == true)
	{
		Serial.print("Accelerometer Ready");
		Serial.print("\n");
	}
	
	return true;
}
bool IMUAccessTwo::setupL3G4200D(void)
{
	//All while(Wire.available()); ensure wire is clear before beginning request
	int samples = 2000;
	
	//15 turns device on, others adjust rate and bandwidth
	int ctrlReg1Value = 15 + GYRO_FREQUENCY * 64 + GYRO_DATA_BANDWIDTH * 16;
	while(Wire.available());
	while((writeIMU(L3G4200D_ADDRESS,L3G4200D_CTRL_REG1,ctrlReg1Value)));

	//enables low filter and settings and stuff.
	//NOT PROPERLY PREPARED
	
	/*
	int ctrlReg2Value = L3G4200D_LOW_FILTER;
	while(Wire.available());
	while((writeIMU(L3G4200D_ADDRESS,L3G4200D_CTRL_REG2,ctrlReg2Value)));
	*/

	
	//sets scale of data based on Config value
	int ctrlReg4Value = GYRO_DATA_SCALE * 16;  //sets
	while(Wire.available());
	while((writeIMU(L3G4200D_ADDRESS,L3G4200D_CTRL_REG4,ctrlReg4Value)));

	
	//enables high filter and settings and stuff.
	//NOT PROPERLY PREPARED
	
	/*
	int ctrlReg5Value = L3G4200D_HIGH_FILTER;
	while(Wire.available());
	while((writeIMU(L3G4200D_ADDRESS,L3G4200D_CTRL_REG5,ctrlReg5Value)));
	*/
	
	//prepares offset values, will hopefully make gyro more reliable
	int xSum = 0, ySum = 0, zSum = 0;
	gyroMicros = micros();
	for(int i = 0; i < samples;)
	{
		if(micros()-gyroMicros > gyroInterval)     //Accesses Gyros at frequency from Config
		{
			if(getGyroData()==true)
			{
				xSum += currentGyroValues[0];
				ySum += currentGyroValues[1];
				zSum += currentGyroValues[2];
				i++;
			}
		}
	}
	gyroOffsets[0] = xSum / samples;
	gyroOffsets[1] = ySum / samples;
	gyroOffsets[2] = zSum / samples;
	
	if(DEBUG == true)
	{
		Serial.print("Gyro Ready");
		Serial.print("\n");
		Serial.print("Gyro offsets:\nX= ");
		Serial.print(gyroOffsets[0]); Serial.print("\nY= ");
		Serial.print(gyroOffsets[1]); Serial.print("\nZ= ");
		Serial.print(gyroOffsets[2]); Serial.print("\n");
	}
	return true;
}
bool IMUAccessTwo::setupHMC5883L(void)
{
	//all while(Wire.available()); statements ensure wire is clear before running.
	int configA = 4 * COMPASS_FREQUENCY+ 32 * COMPASS_SAMPLES_AVERAGED;
	while(Wire.available());
	while((writeIMU(HMC5883L_ADDRESS,HMC5883L_CONFIG_A,configA))); //sets gain to


	int configB = 32 * COMPASS_GAIN;
	while(Wire.available());
	while((writeIMU(HMC5883L_ADDRESS,HMC5883L_CONFIG_B,configB))); //sets gain to
	
	
	int dataValue = 0;  //will always run in continuous measurement mode
	while(Wire.available());
	while((writeIMU(HMC5883L_ADDRESS,HMC5883L_DATA,dataValue))); //sets to continuous measurement mode
	
	if(DEBUG == true)
	{
		Serial.print("Compass Ready\n");
	}
	
	return true;

}
bool IMUAccessTwo::setupBMP085(void)
{
}
bool IMUAccessTwo::getAccelData()
{
	byte incomingValues[6] = {0};
	bool goodRead = readIMU(ADXL345_ADDRESS,ADXL345_DATA,6, incomingValues);
	
	if(goodRead == true)
	{
		currentAccelValues[0] = incomingValues[1]<<8 | incomingValues[0];
		currentAccelValues[1] = incomingValues[3]<<8 | incomingValues[2];
		currentAccelValues[2] = incomingValues[5]<<8 | incomingValues[4];
	
	
		int temp;
		for(int i = 0; i < 3; i++)
		{
			temp = currentAccelValues[i];
			if(temp > 32767)   //this means the value is negative, must be fixed
			{
				int j = 31;
				while(bitRead(temp,j)==0) //sign extends number
				{
					bitWrite(temp,j,1);
					j--;
				}
			
				for(j = 0; j < 32; j++)       //gives 2's complement of number
				{	
					if(bitRead(temp,j)==1)
					{
						bitWrite(temp,j,0);
					}
					else
					{
						bitWrite(temp,j,1);
					}
				}
				temp += 1;
				//This is a low pass filter to help a bit with noise
				currentAccelValues[i] = -temp;		
			}
		}
	}
	return goodRead;
}
bool IMUAccessTwo::getGyroData()
{
	byte incomingValues[6] = {0};
	bool goodRead = readIMU(L3G4200D_ADDRESS,L3G4200D_DATA,6, incomingValues);
	
	
	if(goodRead == true)
	{
		currentGyroValues[0] = incomingValues[1]<<8 | incomingValues[0];
		currentGyroValues[1] = incomingValues[3]<<8 | incomingValues[2];
		currentGyroValues[2] = incomingValues[5]<<8 | incomingValues[4];
	
	
		int temp;
		for(int i = 0; i < 3; i++)
		{
			temp = currentGyroValues[i];
			if(temp > 32767)   //this means the value is negative, must fix
			{
				int j = 31;
				while(bitRead(temp,j)==0) //sign extends number
				{
					bitWrite(temp,j,1);
					j--;
				}
			
				for(j = 0; j < 32; j++)       //gives 2's complement of number
				{	
					if(bitRead(temp,j)==1)
					{
						bitWrite(temp,j,0);
					}
					else
					{
						bitWrite(temp,j,1);
					}
				}
				temp += 1;
				currentGyroValues[i] = -temp;		
			}
		}
		//Not sure this is correct
		for(int i = 0; i < 3; i++)
		{
			currentGyroValues[i] = currentGyroValues[i] - gyroOffsets[i];
		}
	}
	return goodRead;
}
bool IMUAccessTwo::getCompassData()
{
	byte incomingValues[6] = {0};
	
	
	bool goodRead = readIMU(HMC5883L_ADDRESS,HMC5883L_DATA,6, incomingValues);
	if(goodRead == true)
	{
		//Not sure this block is appropriate for the compass
		currentCompassValues[0] = incomingValues[0]<<8 | incomingValues[1];
		currentCompassValues[1] = incomingValues[2]<<8 | incomingValues[3];
		currentCompassValues[2] = incomingValues[4]<<8 | incomingValues[5];
	
	
		//Converts the 2's complement number into a negative number as needed
		int temp;
		for(int i = 0; i < 3; i++)
		{
			temp = currentCompassValues[i];
			if(temp > 32767)   //this means the value is negative, must fix
			{
				int j = 31;
				while(bitRead(temp,j)==0) //sign extends number
				{
					bitWrite(temp,j,1);
					j--;
				}
				for(int j = 0; j < 32; j++)       //gives 2's complement of number
				{	
					if(bitRead(temp,j)==1)
					{
						bitWrite(temp,j,0);
					}
					else
					{
						bitWrite(temp,j,1);
					}
				}
				temp += 1;
				currentCompassValues[i] = -temp;		
			}
		}
	}
	return goodRead;
}
bool IMUAccessTwo::readIMU(int deviceAddress, int dataAddress,int numBytes, byte incomingValues[])
{
	bool returnValue = false;
	while(Wire.available()); //This ensures the wire is clear before executing

	Wire.beginTransmission(deviceAddress);
    Wire.write(dataAddress);              //Initial data position order is XZY, NOT XYZ
    int successfulTransmission = Wire.endTransmission();
	
    if(successfulTransmission != 0)
    {
	/*
		if(DEBUG == true)
		{
			Serial.print("read failure on: ");
			Serial.print(deviceAddress);
			Serial.print("due to endTransmission = ");
			Serial.print(successfulTransmission);
			Serial.print("\n");
		}*/
    }
    else
    {
		Wire.requestFrom(deviceAddress, numBytes); // read numBytes bytes
		
		while(Wire.available() < numBytes);
		
		for(byte i = 0; i < numBytes; i++)
		{
			incomingValues[i] = Wire.read();
		}
		returnValue = true;
	}
		
	Wire.endTransmission(true);
	return returnValue;
}
bool IMUAccessTwo::writeIMU(int deviceAddress, int dataAddress,int value)
{
	Wire.beginTransmission(deviceAddress);
	Wire.write(dataAddress);
	Wire.write(value);
	return (Wire.endTransmission(true));
}