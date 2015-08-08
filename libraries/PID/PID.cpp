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
void PIDTwo::updateFlatPID(double currentOrientation[], double currentRotationRates[])
{//this PID loop holds quadcopter in normal Orientation

	//currentOrientation 0 = roll, 1 = pitch, 2 = thrust
	
	//this is supposed to be (flatPitch)- currentOrientation[1] and so on
	//I am uncertain if  this is already the correct implementation
	
	
	double pitchAngleError = -currentOrientation[1];
	double rollAngleError = -currentOrientation[0];
	
	
	//I do not yet know how to calculate this, but it will be done using
	//the gyro rotation rates
	
	
	
	
	double desiredPitchRate = calculatePID(pitchAngleError,pitchAngleCumError, P_PITCH_ANGLE,I_PITCH_ANGLE,D_PITCH_ANGLE);
	double desiredRollRate = calculatePID(rollAngleError,rollAngleCumError, P_ROLL_ANGLE,I_ROLL_ANGLE,D_ROLL_ANGLE);
	
	
	//desired - current
	
	//currentRotationRates are coded in, but still isn't coded
	double pitchRateError = pitchAngleError - currentRotationRates[1];
	double rollRateError = rollAngleError - currentRotationRates[0];
	double yawRateError = -currentRotationRates[3];
	
	
	
	
	
	pitchAdjustment = calculatePID(pitchRateError,pitchRateCumError,P_PITCH_RATE,I_PITCH_RATE,D_PITCH_RATE);
	rollAdjustment = calculatePID(rollRateError,rollRateCumError,P_ROLL_RATE,I_ROLL_RATE,D_ROLL_RATE);
	yawAdjustment = calculatePID(yawRateError,yawRateCumError,P_YAW_RATE,I_YAW_RATE,D_YAW_RATE);
	
	
	
	
	pitchAdjustment *= 	RATE_TO_POWER;
	rollAdjustment *=  	RATE_TO_POWER;
	yawAdjustment *=   	RATE_TO_POWER;
	
	PIDLimits();
}
void PIDTwo::PIDLimits()
{
	if     (pitchAdjustment > MAX_ADJUSTMENT) pitchAdjustment = MAX_ADJUSTMENT;
	else if(pitchAdjustment < MIN_ADJUSTMENT) pitchAdjustment = MIN_ADJUSTMENT;
	
	if	   (rollAdjustment > MAX_ADJUSTMENT) rollAdjustment = MAX_ADJUSTMENT;
	else if(rollAdjustment < MIN_ADJUSTMENT) rollAdjustment = MIN_ADJUSTMENT;
	
	if     (yawAdjustment > MAX_ADJUSTMENT) yawAdjustment = MAX_ADJUSTMENT;
	else if(yawAdjustment < MIN_ADJUSTMENT) yawAdjustment = MIN_ADJUSTMENT;
}
void PIDTwo::updateStablePID(double currentOrientation[], double desiredOrientation[], double currentRotationRates[])
{
	
}
double PIDTwo::calculatePID(double error, double &cumError, double P, double I, double D)
{
	
	int dt = millis() - prevTime;
	prevTime = millis();
	
	double Pcorrection = P*error;
	
	double integral = I * error * dt /1000.0;
	double Icorrection = integral + cumError;
	cumError += integral;
	
	
	//D value may be considered later
	double Dcorrection = 0;
	
	return Pcorrection + Icorrection + Dcorrection;
}
	
	
	
	
	
	
	
	
	
