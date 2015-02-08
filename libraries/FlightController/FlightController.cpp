/*This function sets up the motors and, after receiving values from
the PID loop, 

*/

#include "Arduino.h"
#include "IMUAccess.h"
#include "Config.h"
#include "FlightController.h"
#include "PID.h"
#include "Receiver.h"
#include "Orientation.h"



//these are for testing

void FlightControllerTwo::setupMotors()
{
	//prepares the motor output pins
	pinMode(FRONT_MOTOR_PIN, OUTPUT);
	pinMode(BACK_MOTOR_PIN,  OUTPUT);
	pinMode(LEFT_MOTOR_PIN,  OUTPUT);
	pinMode(RIGHT_MOTOR_PIN, OUTPUT);
	
	digitalWrite( FRONT_MOTOR_PIN, LOW);
    digitalWrite( BACK_MOTOR_PIN,  LOW);
    digitalWrite( LEFT_MOTOR_PIN,  LOW);
    digitalWrite( RIGHT_MOTOR_PIN, LOW);
	
	//brings the Write resolution to 0-2047
	analogWriteResolution(11);
	
	for(int i = 0; i < 4; i++) {motorPower[i] = {0};}
	
	previousPulseTime = 0;
}




void FlightControllerTwo::flightControl()
{
	
	int dt = micros()-previousPulseTime;
	if(dt > RECALCULATE_MOTOR_PERIOD)
	{
		previousPulseTime = micros();
		Orientation.updateOrientation(dt);
		calculateMotorPower();
	}
	//this must
	if(ARMED == true)
	{
		//change constant is necessary because analogWrite has a range of 0-2047
		analogWrite(FRONT_MOTOR_PIN,motorPower[0]*CHANGE_CONSTANT);
		analogWrite(BACK_MOTOR_PIN ,motorPower[1]*CHANGE_CONSTANT);
		analogWrite(LEFT_MOTOR_PIN ,motorPower[2]*CHANGE_CONSTANT);
		analogWrite(RIGHT_MOTOR_PIN,motorPower[3]*CHANGE_CONSTANT);
	}
	
}
void FlightControllerTwo::calculateMotorPower()
{
	//need to update using PID library when it is available
	//just add a period after each PID ex. PID.throttle
	
	if(Receiver.channelWidth[RECEIVER_MODE] <1200)  //This is SAFE mode, motor set to lowest values, this should be mode quad starts up in
	{
		motorPower[0] = MIN_POWER;
		motorPower[1] = MIN_POWER;
		motorPower[2] = MIN_POWER;
		motorPower[3] = MIN_POWER;
		//analogWrite(BACK_MOTOR_PIN,1000);
	}
	//flat mode, listens to throttle
	else if(1700 > Receiver.channelWidth[RECEIVER_MODE] &&Receiver.channelWidth[RECEIVER_MODE] >1200) //currently hold flat orientation mode
	{//flat mode, listens to throttle, but maintains a vertical orientation
	
	/*  May be removed as later code does power checks
		int throttle;
		if(throttle < MIN_POWER)      throttle = MIN_POWER;
		else if(throttle > MAX_POWER) throttle = MAX_POWER;
		*/
		
		PID.updateFlatPID(Orientation.currentOrientation, Orientation.currentGyroRates);
		int throttle = Receiver.channelWidth[RECEIVER_THROTTLE];
		
		
		//Following segment calculates desired motor changes 
		motorPower[0] = throttle + PID.pitchAdjustment + PID.yawAdjustment;
		motorPower[1] = throttle - PID.pitchAdjustment + PID.yawAdjustment;
		motorPower[2] = throttle + PID.rollAdjustment  - PID.yawAdjustment;
		motorPower[3] = throttle - PID.rollAdjustment  - PID.yawAdjustment;
		
		
		
		
		//Following ensures value is within given parameters, attempts to equally level
		//all inputs if a value is out of range
		int undershoot, overshoot;
		for(int i = 0; i < 4; i++)
		{
			if(MIN_POWER - motorPower[i] > undershoot) undershoot = MIN_POWER - motorPower[i];
			if(motorPower[i] - MAX_POWER > overshoot)  overshoot = motorPower[i] - MAX_POWER;
		}
		for(int i = 0; i < 4; i++)
		{
			motorPower[0] += undershoot - overshoot;
		}
		for(int i = 0; i < 4; i++)
		{
			if(MIN_POWER - motorPower[i] > undershoot) {motorPower[i] = MIN_POWER;}
			if(motorPower[i] - MAX_POWER > overshoot)  {motorPower[i] = MAX_POWER;}
		}
	}
	else   //Controlled by receiver (stable mode)
	{
		double rotationRates[] = {0,0,0,0}; //this line will be changed once minh gets his shit together
		PID.updateStablePID(Orientation.currentOrientation, Orientation.desiredOrientation, rotationRates);
	}
	
}