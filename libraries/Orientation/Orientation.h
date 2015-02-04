#ifndef Orientation_h
#define Orientation_h
#include "Arduino.h"

#define ORIENT_PERIOD 10000 //10,000 microseconds = 100Hz

class OrientationTwo
{
	public:
		void updateOrientation();
		void setupOrientation();
		double roll;
		double pitch;
		double thrust;
		double gx, gy, gz;
		
		double currentOrientation[3];
		double desiredOrientation[3];
		
		private:
		int previousTime;
	
};
extern OrientationTwo Orientation;




#endif