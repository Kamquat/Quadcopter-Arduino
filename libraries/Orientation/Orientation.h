#ifndef Orientation_h
#define Orientation_h
#include "Arduino.h"

#define ORIENT_PERIOD 10000 //10,000 microseconds = 100Hz

class OrientationTwo
{
	public:
		void updateOrientation();
		
		double xyzDegree[3];

};
extern OrientationTwo Orientation;




#endif