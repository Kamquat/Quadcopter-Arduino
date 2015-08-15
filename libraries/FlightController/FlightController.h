#ifndef FlightController_h

#define FlightController_h
#include "Arduino.h"


#define MIN_SAFE_POWER 	1000
#define MIN_POWER 		1050
#define MAX_POWER 		1950
#define MAX_SAFE_POWER 	1980 //Note: due to adjustment, 2000 would be constant ON, not workable
#define CHANGE_CONSTANT 2047./2000


class FlightControllerTwo
{
	
	public:
		void setupMotors();
		void flightControl();
		int flightMode;
		int motorPower[4];
		void calibrateESC();
		
	private:
		int previousPulseTime;
		void updateMotorPower(void);
		void calculateMotorPower(void);
		void checkMotorInputs(void);
		
};
extern FlightControllerTwo FlightController;
#endif