#include "Arduino.h"
#include "Config.h"
#include "AngularPosition.h"
#include "IMUAccess.h"
#include "math.h"


double Gyro_to_degree(double);

void AngularPositionTwo::setupAngularPosition()
{
	double X_Change = 0.0; //initial rate at t = 0
	double y_Change = 0.0;
	double Z_Change = 0.0;
	prevTime = 0;
}

void AngularPositionTwo::updateAngularPosition()
{
	double X_Change = Gyro_to_degree(IMUAccess.currentGyroValues[0]);
	double Y_Change = Gyro_to_degree(IMUAccess.currentGyroValues[1]);
	double Z_Change = Gyro_to_degree(IMUAccess.currentGyroValues[2]);
	

	int dt = prevTime - millis();
	prevTime = millis();
	X_angle += X_Change*dt / 1000; //update value every 10ms
	Y_angle += Y_Change*dt / 1000;
	Z_angle += Z_Change*dt / 1000;
	
}

double Gyro_to_degree(double data_raw)
{
	double Change = 0.0;
	double Sensitivity = 0.00875;
	Change = data_raw*Sensitivity;
	return Change;
}
