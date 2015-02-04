/*
This class takes values for the current orientation, as well as desired orientation
taken from the Orientation library and the Remote library and calculates pitch/Yaw/Roll
adjustments. Further study is needed to know whether it also adjusts for throttle

currentOrientation[0-4] roll,pitch,thrust, YAW(unprogrammed)
*/

#include "Arduino.h"
#include "PID.h"
#include "Config.h"

void PIDTwo::setupPID()
{


	//remove garbage values
	int pitchAdjustment = 0;
	int yawAdjustment = 0;
	int rollAdjustment = 0;
	
	int IValuesCount = 0;
	prevTime = millis();
	
	
	
	
	//this stores values for the I values
	pitchAngleCumError = 0;
	rollAngleCumError = 0;
	
	pitchRateCumError = 0;
	rollRateCumError = 0;
	yawRateCumError = 0;
}
void PIDTwo::updateFlatPID(double[] currentOrientation, double[] currentRotationRates)
{//this PID loop holds quadcopter in normal Orientation

	//currentOrientation 0 = roll, 1 = pitch, 2 = thrust
	
	//this is supposed to be (flatPitch)- currentOrientation[1] and so on
	//I am uncertain if  this is already the correct implementation
	pitchAngleError = -currentOrientation[1];
	rollAngleError = -currentOrientation[0];
	
	pitchAngleCumError+=pitchAngleError;
	rollAngleCumError+=rollAngleError
	
	//I do not yet know how to calculate this, but it will be done using
	//the gyro rotation rates
	pitchRateCumError += 0;
	rollRateCumError  += 0;
	yawRateCumError   += 0;
	
	
	
	
	double desiredPitchRate = calculatePID(currentOrientation[1],pitchAngleCumError);
	double desiredRollRate = calculatePID(currentOrientation[0],rollAngleCumError);
	
	pitchAdjustment = calculatePID(currentRotationRates[1],pitchRateCumError);
	rollAdjustment = calculatePID(currentRotationRates[0],rollRateCumError);
	yawAdjustment = calculatePID(currentRotationRates[2],yawRateCumError);
	
	
	//XXXX_ERROR_TO_POWER converts the degrees into motor power, 
	//uncertain of value yet
	
	//P SEGMENT
	//Pitch/Roll come in -180:180
	
	/*
	tPitchAngleAdjustment = Pcorrection * pitchAngleError;
	tRollAngleAdjustment = Pcorrection * rollAngleError;
	tYawAngleAdjustment = Pcorrection * yawAngleError;
	*/
	
	//I SEGMENT
	
	
	
	
	
	
	
	
	
	

}
void PIDTwo::updateStablePID(double[] currentOrientation, double[] desiredOrientation, double[] currentRotationRates)
{
	
}
void calculatePID(double currentRate, double Error)
{
	
	dt = millis() - prevTime;
	prevTime = millis();
	
	
	
	
	
	
	
	
	
	
	
	
	
}