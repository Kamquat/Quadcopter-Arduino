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
	
	
	pinMode(FRONT_LEFT_MOTOR_PIN, OUTPUT);
	pinMode(FRONT_RIGHT_MOTOR_PIN,  OUTPUT);
	pinMode(BACK_LEFT_MOTOR_PIN,  OUTPUT);
	pinMode(BACK_RIGHT_MOTOR_PIN, OUTPUT);
	
	digitalWrite( FRONT_LEFT_MOTOR_PIN, LOW);
    digitalWrite( FRONT_RIGHT_MOTOR_PIN,  LOW);
    digitalWrite( BACK_LEFT_MOTOR_PIN,  LOW);
    digitalWrite( BACK_RIGHT_MOTOR_PIN, LOW);
	
	//brings the Write resolution to 0-2047
	analogWriteResolution(11);
	
	
	/*
	if(ARMED == true)
	{
		This block is to test connection to motor
		for(int i = 0; i < 4; i++) {motorPower[i] = {MIN_POWER};}
		analogWrite(FRONT_LEFT_MOTOR_PIN,motorPower[0]*CHANGE_CONSTANT);
		analogWrite(FRONT_RIGHT_MOTOR_PIN ,motorPower[1]*CHANGE_CONSTANT);
		analogWrite(BACK_LEFT_MOTOR_PIN ,motorPower[2]*CHANGE_CONSTANT);
		analogWrite(BACK_RIGHT_MOTOR_PIN,motorPower[3]*CHANGE_CONSTANT);
		
		delay(2000);
		analogWrite(FRONT_LEFT_MOTOR_PIN,(motorPower[0]+200)*CHANGE_CONSTANT);
		analogWrite(FRONT_RIGHT_MOTOR_PIN ,(motorPower[1]+200)*CHANGE_CONSTANT);
		analogWrite(BACK_LEFT_MOTOR_PIN ,(motorPower[2]+200)*CHANGE_CONSTANT);
		analogWrite(BACK_RIGHT_MOTOR_PIN,(motorPower[3]+200)*CHANGE_CONSTANT);
		Serial.print("WRITINGSTUFFS\n");
	}
	*/
	previousPulseTime = 0;
}




void FlightControllerTwo::flightControl()
{
	
	int dt = micros()-previousPulseTime;
	if(dt > RECALCULATE_MOTOR_PERIOD)
	{
		
		Receiver.checkInputs();
		Orientation.updateOrientation();
		calculateMotorPower();
		previousPulseTime = micros();

		
		//this must to ensure safe usage
		#if ARMED
			//change constant is necessary because analogWrite has a range of 0-2047
			analogWrite(FRONT_LEFT_MOTOR_PIN,motorPower[0]*CHANGE_CONSTANT);
			analogWrite(FRONT_RIGHT_MOTOR_PIN ,motorPower[1]*CHANGE_CONSTANT);
			analogWrite(BACK_LEFT_MOTOR_PIN ,motorPower[2]*CHANGE_CONSTANT);
			analogWrite(BACK_RIGHT_MOTOR_PIN,motorPower[3]*CHANGE_CONSTANT);
		#else
			digitalWrite(FRONT_LEFT_MOTOR_PIN, LOW);
			digitalWrite(FRONT_RIGHT_MOTOR_PIN, LOW);
			digitalWrite(BACK_LEFT_MOTOR_PIN, LOW);
			digitalWrite(BACK_RIGHT_MOTOR_PIN, LOW);
		#endif
	}	
}
void FlightControllerTwo::calculateMotorPower()
{
	//need to update using PID library when it is available
	//just add a period after each PID ex. PID.throttle
	
	
	//this will control different flight modes
	//0 is motors motor shut-off
	//1 is motor listen to throttle only
	//2 is motors listen to throttle + stabilize (flat mode)
	//3 is motor follow receiver completely (stable mode)
	
	int ReceiverLastUpdated = micros() - Receiver.lastUpdated;
	int throttle = Receiver.channelWidth[RECEIVER_THROTTLE];
	
	if(ReceiverLastUpdated > 1 * 1000000)
	{
		flightMode = 0;
	}
	else if(Receiver.channelWidth[RECEIVER_MODE] <1200)
	{
		flightMode = 1;
	}
	else if(1700 > Receiver.channelWidth[RECEIVER_MODE] &&Receiver.channelWidth[RECEIVER_MODE] >1200)
	{
		flightMode = 2;
	}
	else if(Receiver.channelWidth[RECEIVER_MODE] > 1700)
	{
		flightMode = 3;
	}
	if(flightMode == 0) //This is for when receiver is not detected
	{
		motorPower[0] = MIN_POWER-50;
		motorPower[1] = MIN_POWER-50;
		motorPower[2] = MIN_POWER-50;
		motorPower[3] = MIN_POWER-50;
	}
	else if(flightMode == 1)  //This is flight mode 1, should remain engine cutoff
	{
		
		//This code is useful for calibrating ESCs
		/*
		if(throttle > 1500)
		{
			motorPower[0] = MAX_POWER;
			motorPower[1] = MAX_POWER;
			motorPower[2] = MAX_POWER;
			motorPower[3] = MAX_POWER;
		}
		else
		{
			motorPower[0] = MIN_POWER;
			motorPower[1] = MIN_POWER;
			motorPower[2] = MIN_POWER;
			motorPower[3] = MIN_POWER;
		}*/
		
		motorPower[0] = MIN_POWER-50;
		motorPower[1] = MIN_POWER-50;
		motorPower[2] = MIN_POWER-50;
		motorPower[3] = MIN_POWER-50;
	}
		
		/*
		This code is useful for calibrating ESCs
		if(throttle > 1500)
		{
			motorPower[0] = MAX_POWER;
			motorPower[1] = MAX_POWER;
			motorPower[2] = MAX_POWER;
			motorPower[3] = MAX_POWER;
		}
		else
		{
			motorPower[0] = MIN_POWER;
			motorPower[1] = MIN_POWER;
			motorPower[2] = MIN_POWER;
			motorPower[3] = MIN_POWER;
		}*/
		//analogWrite(BACK_MOTOR_PIN,1000);
	else if(flightMode == 2)   //This is flight mode 2, currently listen to throttle mode
	{
		motorPower[0] = throttle;
		motorPower[1] = throttle;
		motorPower[2] = throttle;
		motorPower[3] = throttle;
		
	}
	else if(flightMode == 3) //Flight mode 3, currently flat mode
	{
	//flat mode, listens to throttle, but maintains a vertical orientation
	
		
		PID.updateFlatPID(Orientation.currentPitch,Orientation.currentRoll, Orientation.currentGyroRates);
		
		
		//Following segment calculates desired motor changes 
		//X configuration
		motorPower[0] = throttle;
		motorPower[1] = throttle;
		motorPower[2] = throttle;
		motorPower[3] = throttle;
		
		motorPower[0] += PID.pitchAdjustment;
		motorPower[1] += PID.pitchAdjustment;
		motorPower[2] += -PID.pitchAdjustment;
		motorPower[3] += -PID.pitchAdjustment;
		
		motorPower[0] += PID.rollAdjustment;
		motorPower[1] += -PID.rollAdjustment;
		motorPower[2] += PID.rollAdjustment;
		motorPower[3] += -PID.rollAdjustment;
		/*
		motorPower[0] += throttle + PID.pitchAdjustment + PID.yawAdjustment;
		motorPower[1] += throttle + PID.pitchAdjustment + PID.yawAdjustment;
		motorPower[2] += throttle - PID.rollAdjustment  - PID.yawAdjustment;
		motorPower[3] += throttle - PID.rollAdjustment  - PID.yawAdjustment;*/
		
		
		
		
		//Following ensures value is within given parameters, attempts to equally level
		//all inputs if a value is out of range
		checkMotorInputs();
	}
}
void FlightControllerTwo::checkMotorInputs()
{
	int undershoot = 0, overshoot = 0;
	for(int i = 0; i < 4; i++)
	{
		if(MIN_POWER - motorPower[i] > undershoot) undershoot = MIN_POWER - motorPower[i];
		if(motorPower[i] - MAX_POWER > overshoot)  overshoot = motorPower[i] - MAX_POWER;
	}
	for(int i = 0; i < 4; i++)
	{
		motorPower[i] += undershoot - overshoot;
	}
	for(int i = 0; i < 4; i++)
	{
		if(motorPower[i] < MIN_POWER) {motorPower[i] = MIN_POWER;}
		if(motorPower[i] > MAX_POWER)  {motorPower[i] = MAX_POWER;}
	}
}