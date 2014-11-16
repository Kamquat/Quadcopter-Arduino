#include "Arduino.h"
#include "Config.h"
#include "Orientation.h"
#include "IMUAccess.h"
#include "math.h"


void OrientationTwo::updateOrientation() 
{
	
	double ax = .0087*IMUAccess.currentAccelValues[0];
	double ay = .0087*IMUAccess.currentAccelValues[1];
	double az = .0087*IMUAccess.currentAccelValues[2];
	
	double xAngle = atan( ax / (sqrt((ay)*(ay) + (az)*(az))));
	double yAngle = atan( ay / (sqrt((ax)*(ax) + (az)*(az))));
	double zAngle = atan( sqrt((ax)*(ax) + (ay)*(ay)) / az);

	xAngle *= 180.00;   yAngle *= 180.00;   zAngle *= 180.00;
	xAngle /= 3.141592; yAngle /= 3.141592; zAngle /= 3.141592;
	
	xyzDegree[0] = xAngle;
	xyzDegree[1] = yAngle;
	xyzDegree[2] = zAngle;
	
	if(DEBUG == true)
	{
	Serial.print("Values:\n");
	Serial.print(xAngle);
	Serial.print("\t");
	Serial.print(yAngle);
	Serial.print("\t");
	Serial.print(zAngle);
	Serial.print("\n");
	//delay(2000);
	}
	
}