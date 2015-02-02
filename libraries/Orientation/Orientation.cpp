/* takes inputs from the accelerometer and remote, 
and produces values for current roll/pitch/thust (eventually heading)
as well as the desired version of those values from the remote



INPUTS:
IMUAccess.currentAccelValues[0,1,2]

OUTPUTS
currentOrientation[0-3]    {roll,pitch,thrust,heading}
desiredOrientation[0-3]    {roll,pitch,thrust,heading}

*/

#include "Arduino.h"
#include "Config.h"
#include "Orientation.h"
#include "IMUAccess.h"
#include "math.h"

double Accel_to_G(double);
void OrientationTwo::setupOrientation()
{
	previousTime = 0;
	roll = 0;
	pitch = 0;
	thrust = 0;
}
void OrientationTwo::updateOrientation()
{
	int currentTime = micros();
	if(currentTime - previousTime > ORIENT_PERIOD)
	{
		previousTime = currentTime;
		
		double ax = Accel_to_G(IMUAccess.currentAccelValues[0]);
		double ay = Accel_to_G(IMUAccess.currentAccelValues[1]);
		double az = Accel_to_G(IMUAccess.currentAccelValues[2]);
		
		roll = atan2(-ay,az);
		pitch = atan2( ax,(sqrt((ay)*(ay) + (az)*(az))));
		thrust = sqrt((ax)*(ax) + (ay)*(ay) + (az)*(az));

		roll *= 180.00;   pitch *= 180.00;   //zAngle *= 180.00;
		roll /= 3.141592; pitch /= 3.141592; //zAngle /= 3.141592;
		
		currentOrientation[0] = roll;
		currentOrientation[1] = pitch;
		currentOrientation[2] = thrust;
	}
}

double Accel_to_G(double x)
	{
	/*
		double y = 0;
		if(x < 0)
		{
			y = x * .0071;
		}
		else
		{
			y = x * .0087;
		}*/
		
	
		double y = 0;
		double f = (.0016)/(ACCEL_RESOLUTION*((1/.0071)+(1/.0087)));
		
			if (x <= (ACCEL_RESOLUTION*((1/.0071)+(1/.0087)))/2)
			{
				y = x*(((ACCEL_RESOLUTION/.0071) - abs(x))*f + .0071);
			}
	
			else
			{
				y = x*(-((ACCEL_RESOLUTION/.0087) - abs(x))*f + .0087);
			}
	
		return y;
		
	}