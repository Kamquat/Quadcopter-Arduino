/* takes inputs from the accelerometer and remote, 
and produces values for current roll/pitch/thrust (eventually heading)
as well as the desired version of those values from the remote

INPUTS:
IMUAccess.currentAccelValues[0,1,2]

OUTPUTS
currentOrientation[0-3]    {roll,pitch,thrust,heading}
desiredOrientation[0-3]    {roll,pitch,thrust,heading}

ACCEL_RESOLUTION == 0 => [.0035 - .0043]	(min and max scale factors)
ACCEL_RESOLUTION == 1 => [.0071 - .0087]
ACCEL_RESOLUTION == 2 => [.0141 - .0175]
ACCEL_RESOLUTION == 3 => [.0286 - .0345]
*/

#include "Arduino.h"
#include "Config.h"
#include "Orientation.h"
#include "IMUAccess.h"
#include "math.h"

double Accel_to_G(double,int);
int c[3][2] = { {-126,133},		//x min and max calibration measurements
				{-128,130},		//y
				{-140,115} };	//z
				
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
		
		gx = Accel_to_G(IMUAccess.currentAccelValues[0],0);				//computes gravitational force in x directions
		gy = Accel_to_G(IMUAccess.currentAccelValues[1],1);				//computes gravitational force in y directions
		gz = -1.0*Accel_to_G(IMUAccess.currentAccelValues[2],2);		//gravitational force in z directions. -1 due to mounted position
		
		roll = atan2(gy,gz);											//converts g-force into radians(roll)
		pitch = atan2(-gx,(sqrt((gy)*(gy) + (gz)*(gz))));				//converts g-force into radians(pitch)
		thrust = sqrt((gx)*(gx) + (gy)*(gy) + (gz)*(gz));				//magnitude of all forces (if stationary, should = 1)

		roll *= 180.00;   pitch *= 180.00;   //zAngle *= 180.00; 		converts radians into degrees
		roll /= 3.141592; pitch /= 3.141592; //zAngle /= 3.141592;		converts radians into degrees
		
		currentOrientation[0] = roll;
		currentOrientation[1] = pitch;
		currentOrientation[2] = thrust;
	}
}

double Accel_to_G(double Accel_Value,int axis)					
	{	

		double G = 0, min_factor = 0, max_factor = 0;
		int xmin = c[0][0],xmax = c[0][1],								//sets min and max calibrations to variables for easier use
			ymin = c[1][0],ymax = c[1][1],
			zmin = c[2][0],zmax = c[2][1];
			
			switch (axis) {												//determines which axis function is looking at
			case 0:								//x-axis
				min_factor = (1.0/abs(xmin));	//computes minimum scale factor
				max_factor = (1.0/xmax);		//computes maximum scale factor
				break;
			case 1:								//y-axis
				min_factor = (1.0/abs(ymin));	//computes minimum scale factor
				max_factor = (1.0/ymax);		//computes maximum scale factor
				break;
			case 2:								//z-axis
				min_factor = (1.0/abs(zmin));	//computes minimum scale factor
				max_factor = (1.0/zmax);		//computes maximum scale factor
				break;
			default:
				Serial.print("No axis detected, abort abort.");
				break;
			}
			if (Accel_Value <= 0)					//if int value < 0 use minimum scale factor (g/LSB)
			{
				G = Accel_Value*min_factor;
			}
	
			else									//if positive use maximum scale factor (g/LSB)
			{
				G = Accel_Value*max_factor;
			}
		return G;									//returns value in gravitational force
		
	}