#ifndef Motors_h

#define Motors_h
#include "Arduino.h"

#define ESC_SIGNAL_PERIOD 10000 //10,000 microseconds 100Hz

#define FRONT_MOTOR_PIN 2
#define BACK_MOTOR_PIN 3
#define LEFT_MOTOR_PIN 4
#define RIGHT_MOTOR_PIN 5

#define MIN_THROTTLE 1050
#define MAX_THROTTLE 1950


class motorsTwo
{
	
	public:
		void setupMotors();
		void updateMotors();
		
	private:
		int previousPulseTime;
		bool motorState[4];
		int motorPower[4];
};

#endif