#include "Arduino.h"
#include "IMUAccess.h"
#include "Config.h"
#include "Motors.h"
//#include "PID.h"

//these are for testing
int PIDthrottle = 1500;
int PIDpitchAdjustment = 200;
int PIDyawAdjustment = 150;
int PIDrollAdjustment = 300;
void updateMotorPower();
void updateMotors();

void motorsTwo::setupMotors()
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
	motorState[0] = false; 
	motorState[1] = false; 
	motorState[2] = false; 
	motorState[3] = false;
	
	for(int i = 0; i < 4; i++) {motorPower[i] = {0};}
	
	previousPulseTime = 0;
}
void motorsTwo::updateMotors()
{
	
	int currentTime = micros();
	if(currentTime - previousPulseTime > ESC_SIGNAL_PERIOD)
	{
		digitalWrite( FRONT_MOTOR_PIN, HIGH);
		digitalWrite( BACK_MOTOR_PIN,  HIGH);
		digitalWrite( LEFT_MOTOR_PIN,  HIGH);
		digitalWrite( RIGHT_MOTOR_PIN, HIGH);
		motorState[0] = true; 
		motorState[1] = true; 
		motorState[2] = true; 
		motorState[3] = true;
		updateMotorPower();
		previousPulseTime = currentTime;
	}
	if(motorState[0] && currentTime - previousPulseTime > motorPower[0]) 
		{digitalWrite(FRONT_MOTOR_PIN,LOW);motorState[0] = false;}
		
	if(motorState[1] && currentTime - previousPulseTime > motorPower[1]) 
		{digitalWrite(BACK_MOTOR_PIN, LOW);motorState[1] = false;}
		
	if(motorState[2] && currentTime - previousPulseTime > motorPower[2]) 
		{digitalWrite(LEFT_MOTOR_PIN, LOW);motorState[2] = false;}
		
	if(motorState[3] && currentTime - previousPulseTime > motorPower[3]) 
		{digitalWrite(RIGHT_MOTOR_PIN,LOW);motorState[3] = false;}
}
void motorsTwo::updateMotorPower()
{
	//need to update using PID library when it is available
	//just add a period after each PID ex. PID.throttle
	int throttle;
	if(PIDthrottle < MIN_POWER)      throttle = MIN_POWER;
	else if(PIDthrottle > MAX_POWER) throttle = MAX_POWER;
	
	motorPower[0] = throttle + PIDpitchAdjustment + PIDyawAdjustment;
	motorPower[1] = throttle - PIDpitchAdjustment + PIDyawAdjustment;
	motorPower[2] = throttle + PIDrollAdjustment  - PIDyawAdjustment;
	motorPower[3] = throttle - PIDrollAdjustment  - PIDyawAdjustment;
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