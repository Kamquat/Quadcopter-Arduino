#include "Arduino.h"
#include "Config.h"
#include "Orientation.h"
#include "IMUAccess.h"
#include "math.h"


void OrientationTwo::updateOrientation() 
{
	
	double x = IMUAccess.currentAccelValues[0];
	double y = IMUAccess.currentAccelValues[1];
	double z = IMUAccess.currentAccelValues[2];
	double f = (.0016)/(4*((1/.0071)+(1/.0087)));

	double ax = x*(((4/.0071) - abs(x))*f + .0071);
	double ay = y*(((4/.0071) - abs(y))*f + .0071);
	double az = z*(((4/.0071) - abs(z))*f + .0071);
	
	/*Serial.print(ax);
	Serial.print("\t");
	Serial.print(ay);
	Serial.print("\t");
	Serial.print(az);
	Serial.print("\n");*/
	
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
	//delay(2000);
	}
	
}