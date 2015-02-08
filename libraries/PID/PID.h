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
	double calculatePID(double,double&,double,double,double);
	
	
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
#define RATE_TO_POWER 100.0
//#define NUMBER_CUM_ERROR_SAMPLES	20

extern PIDTwo PID;
#endif