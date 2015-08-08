#ifndef Orientation_h
#define Orientation_h
#include "Arduino.h"
#include "Kalman.h"

#define COMPLEMENT_CONST .95

class OrientationTwo
{
	public:
		void updateOrientation(int);
		void setupOrientation();
		
		double currentOrientation[3];
		double desiredOrientation[3];
		
		double currentGyroRates[3];
		
		void updateKalman();
		void initializeKalman();
		
		KalmanData pitchKalman;
		KalmanData rollKalman;
		
		
		
		//begin Minh's segment
		
		void setupAngularPosition();
		void updateAngularPosition(int);
		
		double X_angle;
		double Y_angle;
		double Z_angle;

		double axisChange[3];
		
		
		
		
		private:
		int previousTime;
		long prevKalmanCalculation;
		//minh's
		int prevTime;
	
};
extern OrientationTwo Orientation;





#endif