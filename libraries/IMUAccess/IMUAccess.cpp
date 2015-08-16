/*
Compass and Barometer not yet ready
*/
#include "IMUAccess.h"
#include "Arduino.h"
#include "Wire.h"
#include "Config.h"
bool IMUAccessTwo::setupDevices(void)
{
	#if DEBUG
		Serial.println("\t\tEntering setupADXL345");
	#endif
	
	setupADXL345();   	//Accelerometer
	
	#if DEBUG
		Serial.println("\t\tEntering L3G4200D");
	#endif
	
	setupL3G4200D(); 	//Gyroscopes
	
	#if DEBUG
		Serial.println("\t\tEntering HMC5883");
	#endif
	
	setupHMC5883L(); 	//Compass	
	
	#if DEBUG
		Serial.println("\t\tEntering BMP085");
	#endif
	
	setupBMP085();		//Barometer
	
	
	#if DEBUG
		Serial.print("IMU Ready\n");
	#endif


}
bool IMUAccessTwo::setupADXL345(void)
{
	//this line clears the bus and should help in cases where the IMU still has data
	//when the arduino restarts
	
	int dataFormatValue = 32 + ACCEL_RESOLUTION; //allows g setting to be enabled in config
	//Writes a a 00101000 to the Power control bit
	//Turns accelerometer into Measurement mode and disables autosleep
	
	//the extra Whiles ensure the write is successful
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
	while((writeIMU(ADXL345_ADDRESS,ADXL345_POWER_CTL,40)));
	
	
	//sets accelerometer to value set in ACCEL_FREQUENCY, 800Hz-100Hz
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
	while((writeIMU(ADXL345_ADDRESS,ADXL345_DATA_RATE,ACCEL_FREQUENCY)));
	
	
	//writes a 32 + ACCEL_RESOLUTION
	//sets g range, right justifies data and enables full resolution
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
	while((writeIMU(ADXL345_ADDRESS,ADXL345_DATA_FORMAT,dataFormatValue)));
	
	
	//Disables all extra settings on accelerometer
	//will change as new options are added
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
	while((writeIMU(ADXL345_ADDRESS,ADXL345_INT_ENABLE,0)));
	
	#if DEBUG
		Serial.print("Accelerometer Ready");
		Serial.print("\n");
	#endif
	
	return true;
}
bool IMUAccessTwo::setupL3G4200D(void)
{
	//All while(Wire.available()); ensure wire is clear before beginning request
	
	//15 turns device on, others adjust rate and bandwidth
	int ctrlReg1Value = 15 + GYRO_FREQUENCY * 64 + GYRO_DATA_BANDWIDTH * 16;
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
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
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
	while((writeIMU(L3G4200D_ADDRESS,L3G4200D_CTRL_REG4,ctrlReg4Value)));

	
	//enables high filter and settings and stuff.
	//NOT PROPERLY PREPARED
	
	/*
	int ctrlReg5Value = L3G4200D_HIGH_FILTER;
	while(Wire.available());
	while((writeIMU(L3G4200D_ADDRESS,L3G4200D_CTRL_REG5,ctrlReg5Value)));
	*/
	
	//prepares offset values, will hopefully make gyro more reliable
	
	#if DEBUG
		Serial.println("Gyro Ready");
		Serial.print("Gyro offsets:\nX= "); Serial.println(gyroOffsets[0]); 
		Serial.print("Y= "); Serial.println(gyroOffsets[1]); 
		Serial.print("Z= "); Serial.println(gyroOffsets[2]);
	#endif
	return true;
}
void IMUAccessTwo::calculateGyroOffsets(long )
{
	double gyroInterval = 0;

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

	int xSum = 0, ySum = 0, zSum = 0;
	long gyroMicros = micros();
	double tempGyroValues[3] = {0};
	for(int i = 0; i < NUM_GYRO_OFFSET_SAMPLES;)
	{
		if(micros()-gyroMicros > gyroInterval)     //Accesses Gyros at frequency from Config
		{
			if(getGyroData(tempGyroValues)==true)
			{
				xSum += tempGyroValues[0];
				ySum += tempGyroValues[1];
				zSum += tempGyroValues[2];
				i++;
			}
		}
	}
	gyroOffsets[0] = xSum / NUM_GYRO_OFFSET_SAMPLES;
	gyroOffsets[1] = ySum / NUM_GYRO_OFFSET_SAMPLES;
	gyroOffsets[2] = zSum / NUM_GYRO_OFFSET_SAMPLES;
}
bool IMUAccessTwo::setupHMC5883L(void)
{
	//all while(Wire.available()); statements ensure wire is clear before running.
	int configA = 4 * COMPASS_FREQUENCY+ 32 * COMPASS_SAMPLES_AVERAGED;
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
	while((writeIMU(HMC5883L_ADDRESS,HMC5883L_CONFIG_A,configA))); //sets gain to


	int configB = 32 * COMPASS_GAIN;
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
	while((writeIMU(HMC5883L_ADDRESS,HMC5883L_CONFIG_B,configB))); //sets gain to
	
	
	int dataValue = 0;  //will always run in continuous measurement mode
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing
	while((writeIMU(HMC5883L_ADDRESS,HMC5883L_DATA,dataValue))); //sets to continuous measurement mode
	
	#if DEBUG
		Serial.print("Compass Ready\n");
	#endif
	
	return true;

}
bool IMUAccessTwo::setupBMP085(void)
{
}
bool IMUAccessTwo::getAccelData(double outgoingForces[3])
{
	byte incomingValues[6] = {0};
	double incomingAccelValues[3] = {0};
	bool goodRead = readIMU(ADXL345_ADDRESS,ADXL345_DATA,6, incomingValues);
	
	if(goodRead == true)
	{
		incomingAccelValues = {0,0,0};
		
		incomingAccelValues[0] = incomingValues[1]<<8 | incomingValues[0];
		incomingAccelValues[1] = incomingValues[3]<<8 | incomingValues[2];
		incomingAccelValues[2] = incomingValues[5]<<8 | incomingValues[4];
	
	
		int temp;
		for(int i = 0; i < 3; i++)
		{
			temp = incomingAccelValues[i];
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
				incomingAccelValues[i] = -temp;		
			}
		}
		//flips X-Y axis *-1 to Z axis
		/*
		temp = -incomingAccelValues[0];
		incomingAccelValues[0] = incomingAccelValues[1];
		incomingAccelValues[1] = temp;
		incomingAccelValues[2] = -incomingAccelValues[2];
		*/
		accelToEuler(incomingAccelValues);
		for(int i = 0; i < 3; i++)
		{
			outgoingForces[i] = incomingAccelValues[i];
		}
	}
	return goodRead;
}
void IMUAccessTwo::accelToEuler(double outgoingForces[3])
{
	accelToGForce(outgoingForces[0],ACCELX_MIN_FACTOR,ACCELX_MAX_FACTOR);
	accelToGForce(outgoingForces[1],ACCELY_MIN_FACTOR,ACCELY_MAX_FACTOR);
	accelToGForce(outgoingForces[2],ACCELZ_MIN_FACTOR,ACCELZ_MAX_FACTOR);
}
void IMUAccessTwo::gyroToDegree(double outgoingDegrees[3])
{
	double degree = 0;
	for(int i = 0; i < 3; i++)
	{
		outgoingDegrees[i] = outgoingDegrees[i] *gyroSensitivity;
	}
}
void IMUAccessTwo::calculateGyroSensitivity()
{
	//This will eventually calculate it based on config value
	gyroSensitivity = 0.00875;
}
double IMUAccessTwo::accelToGForce(int inValue, double minValue, double maxValue)
{
	//NOTE: The Min/Max values are the accelerometer values
	//when the accelerometer was placed in particular orientations
	//Ex: When X=Z=0 and Y = min / max rotation
	//This means it already accounts for gravity conversion
	double G = 0;
	if (inValue <= 0)					//if int value < 0 use minimum scale factor (g/LSB)
	{
		G = (double)inValue / minValue;
	}
	
	else									//if positive use maximum scale factor (g/LSB)
	{
		G = (double)inValue / maxValue;
	}
	return G;									//returns value in gravitational force	
}
bool IMUAccessTwo::getGyroData(double outgoingDegrees[3])
{
	byte incomingValues[6] = {0};
	double incomingGyroValues[3] = {0};
	bool goodRead = readIMU(L3G4200D_ADDRESS,L3G4200D_DATA,6, incomingValues);
	
	
	if(goodRead == true)
	{
		incomingGyroValues[0] = incomingValues[1]<<8 | incomingValues[0];
		incomingGyroValues[1] = incomingValues[3]<<8 | incomingValues[2];
		incomingGyroValues[2] = incomingValues[5]<<8 | incomingValues[4];
	
	
		int temp;
		for(int i = 0; i < 3; i++)
		{
			temp = incomingGyroValues[i];
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
				incomingGyroValues[i] = -temp;		
			}
		}
		
		//Flips X-Y axis, flips +-Z measurements
		/*
		temp = incomingGyroValues[0];
		incomingGyroValues[0] = incomingGyroValues[1];
		incomingGyroValues[1] = temp;
		incomingGyroValues[2] = -incomingGyroValues[2];
		*/
		
		
		//offsets Gyros
		for(int i = 0; i < 3; i++)
		{
			incomingGyroValues[i] = incomingGyroValues[i] - gyroOffsets[i];
		}
		
		gyroToDegree(incomingGyroValues);
		
		for(int i = 0; i < 3; i++)
		{
			outgoingDegrees[i] = incomingGyroValues[i];
		}
	}
	return goodRead;
}
bool IMUAccessTwo::getCompassData(double outgoingHeading)
{
	//This section is just some basic code, nothing is being done with it
	//will probably require tweaking to work
	byte incomingValues[6] = {0};
	double incomingCompassValues[3] = {0};
	
	
	bool goodRead = readIMU(HMC5883L_ADDRESS,HMC5883L_DATA,6, incomingValues);
	if(goodRead == true)
	{
		//Not sure this block is appropriate for the compass
		incomingCompassValues[0] = (double)(incomingValues[0]<<8 | incomingValues[1]);
		incomingCompassValues[1] = incomingValues[2]<<8 | incomingValues[3];
		incomingCompassValues[2] = incomingValues[4]<<8 | incomingValues[5];
	
	
		//Converts the 2's complement number into a negative number as needed
		int temp;
		for(int i = 0; i < 3; i++)
		{
			temp = incomingCompassValues[i];
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
				incomingCompassValues[i] = -temp;		
			}
		}
		
		
		//will still need to convert this to heading
		for(int i = 0; i < 3; i++)
		{
			currentCompassValues[i] = incomingCompassValues[i];
		}
		//Flips X-Y axis, flips +-Z measurements
		/*
		temp = currentCompassValues[1];
		currentCompassValues[0] = currentCompassValues[1];
		currentCompassValues[1] = temp;
		currentCompassValues[2] = -currentCompassValues[2];
		*/
	}
	return goodRead;
}
bool IMUAccessTwo::readIMU(int deviceAddress, int dataAddress,int numBytes, byte incomingValues[])
{
	bool returnValue = false;
	while(Wire.available()) 
		Wire.endTransmission(true); //This ensures the wire is clear before executing

	Wire.beginTransmission(deviceAddress);
    Wire.write(dataAddress);              //Initial data position order is XZY, NOT XYZ
    int successfulTransmission = Wire.endTransmission();
	
    if(successfulTransmission != 0)
    {
	/*
		#if DEBUG
			Serial.print("read failure on: ");
			Serial.print(deviceAddress);
			Serial.print("due to endTransmission = ");
			Serial.print(successfulTransmission);
			Serial.print("\n");
		#endif*/
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
bool IMUAccessTwo::clearI2CBus()
{
	pinMode(21, OUTPUT);
	for (int i = 0; i < 8; i++) {
		digitalWrite(21, HIGH);
		delayMicroseconds(3);
		digitalWrite(21, LOW);
		delayMicroseconds(3);
	}
	pinMode(21, INPUT);
	
}