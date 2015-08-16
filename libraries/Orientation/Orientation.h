#ifndef Orientation_h
#define Orientation_h
#include "Arduino.h"
#include "Kalman.h"

#define COMPLEMENT_CONST 	.95
#define UP_ANG_POS_PERIOD	1000000./800 //800Hz
#define KALMAN_CALC_PERIOD	1000000./100 //100Hz

class OrientationTwo
{
	public:
		void updateOrientation();
		void setupOrientation();
		
		double currentPitch;
		double currentRoll;
		double desiredOrientation[3];
		
		double currentGyroRates[3];
		
		void updateKalman(int, double, double, double, double);
		void initializeKalman();
		
		Kalman pitchKalman;
		Kalman rollKalman;
		
		float currentKalmanPitch;
		float currentKalmanRoll;
		
		void calculatePitchRoll(void);
		
		//begin Minh's segment
		
		void setupAngularPosition();
		void updateAngularPosition(int);
		
		double X_angle;
		double Y_angle;
		double Z_angle;

		double axisChange[3];
		
		double tPitch;
		double tRoll;
		
		
		private:
		int previousTime;
		long prevKalmanCalculation;
		int accelLastUpdate;
		int gyroLastUpdate;
		int compassLastUpdate;
		double accelInterval;
		double gyroInterval;
		double compassInterval;
		double gyroOffsets[3];
		void updateEulerValues(void);
		
		
		
		//minh's
		int prevTime;
		long previousUpAngPos; //used in angular integral calculation
		long previousKalmanCalc; //used in calculating Kalman Filter
	
};
extern OrientationTwo Orientation;





#endif