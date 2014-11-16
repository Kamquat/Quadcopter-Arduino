#include "Arduino.h"
#include "Config.h"
#include "Orientation.h"


void OrientationTwo::updateOrientation() 
{
	
	double ax = IMUAccess.currentAccelValues[0];
	double ay = IMUAccess.currentAccelValues[1];
	double az = IMUAccess.currentAccelValues[2];
	
	double xAngle = atan( ax / (sqrt(square(ay) + square(az))));
	double yAngle = atan( ay / (sqrt(square(ax) + square(az))));
	double zAngle = atan( sqrt(square(ax) + square(ay)) / az);

	xAngle *= 180.00;   yAngle *= 180.00;   zAngle *= 180.00;
	xAngle /= 3.141592; yAngle /= 3.141592; zAngle /= 3.141592;
	
	xyzDegree[3] = [xAngle yAngle zAngle];
	
	if(DEBUG == true)
	{
	serial.print(xAngle);
	serial.print(yAngle);
	serial.print(zAngle);
	}
	
}