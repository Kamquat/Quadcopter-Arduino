/*
  IMUAccess.h Library for a quadcopter project.
  Created by Samuel L. B., October 11, 2014.
  Released into the public domain.
*/

#ifndef IMUAccess_h
#define IMUAccess_h
#include "Arduino.h"

//
#define NUM_GYRO_OFFSET_SAMPLES	2000	//used in offset calculation


//ACCELEROMETER CALIBRATIONS
#define ACCELX_MIN_FACTOR		-128	
#define ACCELX_MAX_FACTOR		130
#define ACCELY_MIN_FACTOR		-126
#define ACCELY_MAX_FACTOR		133
#define ACCELZ_MIN_FACTOR		115 //may need to flip
#define ACCELZ_MAX_FACTOR		-135



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



//bool public setupHMC5883L();

class IMUAccessTwo
{
	public:
		bool setupDevices();
		int currentAccelValues[3];
		int accelAverageArray[][3];
		int gyroAverageArray[];
		int compassAverageArray[];
		int currentGyroValues[3];
		int currentCompassValues[3];
		void testStuff();
		bool clearI2CBus(void);
		void averageGyroValues(void);
		bool getAccelData(double[3]);
		bool getGyroData(double[3]);
		bool getCompassData(double);
		void getBarometerData(double);
		void calculateGyroOffsets(long);
	private:
		bool setupADXL345();
		bool setupL3G4200D();
		bool setupHMC5883L();
		bool setupBMP085();
		bool readIMU(int,int,int,byte[]);
		bool writeIMU(int,int, int);
		void gyroToDegree(double[3]);
		void accelToEuler(double[3]);
		double accelToGForce(int,double,double);
		
		double gyroSensitivity;
		void calculateGyroSensitivity();
		
		
		int gyroOffsets[3];
		//int retrieveValue(int address, int registerAddress);
	
};
extern IMUAccessTwo IMUAccess;

//extern bool setupHMC5883L();

#endif

