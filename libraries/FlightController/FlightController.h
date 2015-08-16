#ifndef FlightController_h

#define FlightController_h
#include "Arduino.h"



#define MIN_POWER 1050
#define MAX_POWER 1950
#define CHANGE_CONSTANT 2047./2000


class FlightControllerTwo
{
	
	public:
		void setupMotors();
		void flightControl();
		int flightMode;
		int motorPower[4];
		
	private:
		int previousPulseTime;
		void updateMotorPower(void);
		void calculateMotorPower(void);
		void checkMotorInputs(void);
		
};
extern FlightControllerTwo FlightController;
#endif