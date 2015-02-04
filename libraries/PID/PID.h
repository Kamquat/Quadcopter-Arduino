/*
  PID.h Library for a quadcopter project.
  Created by Samuel L. B., October 11, 2014.
  Released into the public domain.
*/
#ifndef PID_h
#define PID_h
#include "Arduino.h"

class PIDTwo
{
	public:
	void updateFlatPID(double[], double[]);
	void updateStablePID(double[], double[], double[]);
	void updateAcroPID(void);
	void setupPID(void);
	
	
	//these are the values used by the flight controller
	int pitchAdjustment;
	int yawAdjustment;
	int rollAdjustment;
	
	
	private:
	double pitchAngleCumError;
	double rollAngleCumError;
	
	
	double pitchRateCumError;
	double rollRateCumError;
	double yawRateCumError;
	
	int prevTime;
};

//500 because motor input range is 1000-2000, and we want half that, may need adjustment
#define PITCH_ERROR_TO_POWER = 500.00/90
#define ROLL_ERROR_TO_POWER = 500.00/180

extern PIDTwo PID;
#endif