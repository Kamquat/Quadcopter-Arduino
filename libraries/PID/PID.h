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
	void calculatePIDAdjustments(void);
	void setupPID(void);
	int pitchAdjustment;
	int yawAdjustment;
	int rollAdjustment;
};
extern PIDTwo PID;
#endif