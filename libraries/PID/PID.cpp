/*
This class takes values for the current orientation, as well as desired orientation
taken from the Orientation library and the Remote library and calculates pitch/Yaw/Roll
adjustments. Further study is needed to know whether it also adjusts for throttle


*/

#include "Arduino.h"
#include "PID.h"
#include "Config.h"

void PIDTwo::setupPID()
{



	//these are for testing
	int pitchAdjustment = 200;
	int yawAdjustment = 150;
	int rollAdjustment = 300;
}

void PIDTwo::calculatePIDAdjustments()
{
	
}