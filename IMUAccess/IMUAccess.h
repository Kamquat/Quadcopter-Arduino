/*
  IMUAccess.h Library for a quadcopter project.
  Created by Samuel L. B., October 11, 2014.
  Released into the public domain.
*/

#ifndef IMUAccess_h
#define IMUAccess_h


//define Accelerometer addresses

#define ADXL345_ADDRESS  0x53     //device address
#define ADXL345_MODE     0x00      //need to add
#define ADXL345_DATA_X0  0x32
#define ADXL345_DATA_X1  0x33
#define ADXL345_DATA_Y0  0x34
#define ADXL345_DATA_Y1  0x35
#define ADXL345_DATA_Z0  0x36
#define ADXL345_DATA_Z1  0x37

//define Gyroscopes addresses
                              
#define L3G4200D_ADDRESS   0x69    //device address
#define L3G4200D_MODE      0x00  //need to define
#define L3G4200D_DATA_X0   0x28
#define L3G4200D_DATA_X1   0x29
#define L3G4200D_DATA_Y0   0x2A
#define L3G4200D_DATA_Y1   0x2B
#define L3G4200D_DATA_Z0   0x2C
#define L3G4200D_DATA_Z1   0x2D

//Define Compass addresses

#define HMC5883L_ADDRESS        0x1E    //device address
#define HMC5883L_MODE           0x02
#define HMC5883L_DATA_X0        0x03
#define HMC5883L_DATA_X1        0x04
#define HMC5883L_DATA_Y0        0x07
#define HMC5883L_DATA_Y1        0x08
#define HMC5883L_DATA_Z0        0x05
#define HMC5883L_DATA_Z1        0x06

//bool public setupHMC5883L();

class IMUAccessTwo
{
public:
	bool setupADXL345();
	bool setupL3G4200D();
	bool setupHMC5883L();
	int getAccelData();
	int getGyroData();
	int getCompassData();
	int getBarometerData();
	
private:
	int retrieveValue(int address, int registerAddress);
	
};
extern IMUAccessTwo IMUAccess;

//extern bool setupHMC5883L();

#endif

