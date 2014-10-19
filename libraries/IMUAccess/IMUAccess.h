/*
  IMUAccess.h Library for a quadcopter project.
  Created by Samuel L. B., October 11, 2014.
  Released into the public domain.
*/

#ifndef IMUAccess_h
#define IMUAccess_h


//define Accelerometer addresses

#define ADXL345_ADDRESS			0x53     //device address
#define ADXL345_INACT			0x27
#define ADXL345_POWER_CTL		0x2D
#define ADXL345_DATA			0x32
#define ADXL345_DATA_FORMAT		0x31

//define Gyroscopes addresses
                              
#define L3G4200D_ADDRESS  		0x69    //device address
#define L3G4200D_MODE     	 	0x00  //need to define
#define L3G4200D_DATA	  		0x28


//Define Compass addresses

#define HMC5883L_ADDRESS        0x1E    //device address
#define HMC5883L_MODE           0x02
#define HMC5883L_DATA	        0x03

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
	int retrieveValue(int address, int registerAddress);
	
private:
	
};
extern IMUAccessTwo IMUAccess;

//extern bool setupHMC5883L();

#endif

