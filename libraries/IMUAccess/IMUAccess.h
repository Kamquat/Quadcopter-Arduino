/*
  IMUAccess.h Library for a quadcopter project.
  Created by Samuel L. B., October 11, 2014.
  Released into the public domain.
*/

#ifndef IMUAccess_h
#define IMUAccess_h
#include "Arduino.h"


//define Accelerometer addresses

#define ADXL345_ADDRESS			0x53     //device address
#define ADXL345_INACT			0x27
#define ADXL345_DATA_RATE       0x2C
#define ADXL345_POWER_CTL		0x2D
#define ADXL345_DATA			0x32
#define ADXL345_DATA_FORMAT		0x31
#define ADXL345_LATENT			0x22
#define ADXL345_INT_ENABLE		0x2E

//define Gyroscopes addresses
                              
#define L3G4200D_ADDRESS  		0x69    //device address
#define L3G4200D_DATA	  		0x28 | (1 << 7)
#define L3G4200D_CTRL_REG1		0x20
#define L3G4200D_CTRL_REG2		0x21
#define L3G4200D_CTRL_REG3		0x22
#define L3G4200D_CTRL_REG4		0x23
#define L3G4200D_CTRL_REG5		0x24

#define L3G4200D_LOW_FILTER     0x34
#define L3G4200D_HIGH_FILTER    0x13



//Define Compass addresses

#define HMC5883L_ADDRESS        0x1E    //device address
#define HMC5883L_CONFIG_A       0x00
#define HMC5883L_CONFIG_B       0x01
#define HMC5883L_MODE			0x02 //this sets the compass to continuous measurement mode
#define HMC5883L_DATA	        0x03



#define ACCEL_LPF_VALUE			.95
#define ACCEL_HPF_VALUE			.9

#define NUMBER_PREV_VALUES		4


//bool public setupHMC5883L();

class IMUAccessTwo
{
	public:
		bool setupDevices();
		void updateIMUValues();
		int currentAccelValues[3];
		int accelAverageArray[][3];
		int gyroAverageArray[];
		int compassAverageArray[];
		int currentGyroValues[3];
		int currentCompassValues[3];
		void testStuff();
		bool clearI2CBus(void);
		void averageGyroValues(void);
	private:
		bool setupADXL345();
		bool setupL3G4200D();
		bool setupHMC5883L();
		bool setupBMP085();
		bool getAccelData();
		bool getGyroData();
		bool getCompassData();
		void getBarometerData();
		bool readIMU(int,int,int,byte[]);
		bool writeIMU(int,int, int);
		
		int incomingAccelValues[3];
		int incomingGyroValues[3];
		
		int accelMicros,gyroMicros,compassMicros;
		int accelInterval, gyroInterval, compassInterval;
		int gyroOffsets[3];
		
		int previousGyroValues[3][NUMBER_PREV_VALUES];
		int gyroAverageCounter;
		//int retrieveValue(int address, int registerAddress);
	
};
extern IMUAccessTwo IMUAccess;

//extern bool setupHMC5883L();

#endif

