#ifndef AngularPosition_h
#define AngularPosition_h
#include "Arduino.h"

#define ORIENT_PERIOD 10000 //10,000 microseconds = 100Hz

class AngularPositionTwo
{ 
	public:
		void setupAngularPosition();
		void updateAngularPosition();
		
		double X_angle;
		double Y_angle;
		double Z_angle;
		
		double currentGyroValues[3];

	private:
		int prevTime;
};

extern AngularPositionTwo AngularPosition;




#endif