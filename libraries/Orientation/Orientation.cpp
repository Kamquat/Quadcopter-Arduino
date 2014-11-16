#include "Arduino.h"
#include "Config.h"
#include "Orientation.h"
#include "IMUAccess.h"
#include "math.h"

double Accel_to_G(double);
void OrientationTwo::updateOrientation()
{
	currentTime = micros();
	if(currentTime - previousTime > ORIENT_PERIOD)
	{
		previousTime = currentTime;
		
		double ax = Accel_to_G(IMUAccess.currentAccelValues[0]);
		double ay = Accel_to_G(IMUAccess.currentAccelValues[1]);
		double az = Accel_to_G(IMUAccess.currentAccelValues[2]);
		
		double roll = atan2(-ay,az);
		double pitch = atan2( ax,(sqrt((ay)*(ay) + (az)*(az))));
		double thrust = sqrt((ax)*(ax) + (ay)*(ay) + (az)*(az));

		roll *= 180.00;   pitch *= 180.00;   //zAngle *= 180.00;
		roll /= 3.141592; pitch /= 3.141592; //zAngle /= 3.141592;
		
		xyzDegree[0] = roll;
		xyzDegree[1] = pitch;
		xyzDegree[2] = thrust;
		
		if(DEBUG == true)
		{
		Serial.print("Values:\n");
		Serial.print("Roll: "); Serial.print(roll);
		Serial.print("\t");
		Serial.print("Pitch: "); Serial.print(pitch);
		Serial.print("\t");
		Serial.print("Thrust: "); Serial.print(thrust);
		Serial.print("\n");
		}
	}
}

double Accel_to_G(double x)
	{
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