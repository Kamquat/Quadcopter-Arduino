#ifndef Motors_h

#define Motors_h
#include "Arduino.h"

#define ESC_SIGNAL_PERIOD 1000000./100 //10,000 microseconds 100Hz


#define MIN_POWER 1050
#define MAX_POWER 1950


class motorsTwo
{
	
	public:
		void setupMotors();
		void updateMotors();
		
	private:
		int previousPulseTime;
		void updateMotorPower(void);
		bool motorState[4];
		int motorPower[4];
};

#endif