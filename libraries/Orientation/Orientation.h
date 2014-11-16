#ifndef Orientation_h

#define Orientation_h
#include "Arduino.h"

class OrientationTwo
{
	public:
		void updateOrientation();
		double xyzDegree[3];

};
extern OrientationTwo Orientation;




#endif