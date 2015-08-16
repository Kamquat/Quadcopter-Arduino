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
#include "Kalman.h"

double Accel_to_G(double,int);
double Gyro_to_degree(double);
				
				/*
				disabled because these values moved to IMUAccess
int c[3][2] = { {-128,130},		//x min and max calibration measurements
				{-126,133},		//y
				{115,-135} };	//z	
*/				
				
void OrientationTwo::setupOrientation()
{
	initializeKalman();
	currentRoll = 0;
	currentPitch = 0;
	//execute Minh's setup
	setupAngularPosition();
	
	
	accelLastUpdate = 0; gyroLastUpdate = 0; compassLastUpdate = 0;
	accelInterval = 0, gyroInterval = 0, compassInterval = 0;
	gyroOffsets[3] = {0};
	int gyroAverageCounter = 0;
	previousUpAngPos = micros();
	
	
	//Sets the updateFrequencies
	#if DEBUG
		Serial.println("Entering switch statements");
	#endif
	switch(ACCEL_FREQUENCY)
	{
		case 13: 	accelInterval = 1000000/800;
					break;
		case 12:	accelInterval = 1000000/400;
					break;
		case 11:	accelInterval = 1000000/200;
					break;
		case 10:	accelInterval = 1000000/100;
					break;
		case 9:		accelInterval = 1000000/50;
					break;
	}
	switch(GYRO_FREQUENCY)
	{
		case 0: 	gyroInterval = 1000000/100;
					break;
		case 1:		gyroInterval = 1000000/200;
					break;
		case 2:		gyroInterval = 1000000/400;
					break;
		case 3:		gyroInterval = 1000000/800;
	}
	switch(COMPASS_FREQUENCY)
	{
		case 3: 	compassInterval = 1000000/7.5;
					break;
		case 4:		compassInterval = 1000000/15;
					break;
		case 5:		compassInterval = 1000000/30;
					break;
		case 6:		compassInterval = 1000000/75;
	}
	
}
void OrientationTwo::updateOrientation()
{
	long currentTime = micros();
	updateEulerValues();
	
	calculatePitchRoll();
	
	if(currentTime - previousUpAngPos > UP_ANG_POS_PERIOD)
		updateAngularPosition(currentTime - previousUpAngPos);
	
	
	
	//int DT, double pitch, double gyroX, double roll, double gyroY
	
	//Note that on the IMU X-Y are flipped and Z is negated
	if(currentTime - previousKalmanCalc > KALMAN_CALC_PERIOD)
	updateKalman(currentTime - previousKalmanCalc,tPitch,currentGyroRates[1],tRoll,currentGyroRates[0]);
	
	
	
	
	
	//These lines are a complementary filter
	//roll
	
	
	currentRoll = (currentRoll + axisChange[0])*COMPLEMENT_CONST;
	currentRoll += tRoll*(1.-COMPLEMENT_CONST);
	
	//pitch
	currentPitch = (currentPitch + axisChange[1]) *COMPLEMENT_CONST;
	currentPitch += tPitch*(1.-COMPLEMENT_CONST);
	
	//thrust
	
	
}
void OrientationTwo::updateEulerValues()
{
	long currentTime = micros();
	double tempAccelValues[3] = {0};
	if(currentTime - accelLastUpdate > accelInterval)
	{
		bool goodAccelRead = IMUAccess.getAccelData(tempAccelValues);
		if(goodAccelRead == true) 
		{
			accelLastUpdate = currentTime;
		}
	}
	if(currentTime - gyroLastUpdate > gyroInterval)
	{
		double tempGyroValues[3] = {0};
		bool goodGyroRead = IMUAccess.getAccelData(tempGyroValues);
		if(goodGyroRead == true)
		{
			gyroLastUpdate = currentTime;
		}
	}
	if(currentTime - compassLastUpdate > compassInterval)
	{
		double heading = 0;
		bool goodCompassRead = IMUAccess.getCompassData(heading);
		if(goodCompassRead == true)
		{
			compassLastUpdate = currentTime;
		}
	}
	
	
	
	
	
	
	
}
void OrientationTwo::calculatePitchRoll()
{
	//NOTE: this flips the X-Y axis and negates Z axis
	//THis is because the IMU is upsidedown and slightly rotated

	/*
	disabled because IMUAccess now handles gravity conversion
	double gx = Accel_to_G(IMUAccess.currentAccelValues[1],1);				//computes gravitational force in x directions
	double gy = Accel_to_G(IMUAccess.currentAccelValues[0],0);				//computes gravitational force in y directions
	double gz = Accel_to_G(-IMUAccess.currentAccelValues[2],2);		        //gravitational force in z directions. 
	*/
	
	
	
	//this flips axis to reorient system
	double gx = IMUAccess.currentAccelValues[1];
	double gy = IMUAccess.currentAccelValues[0];
	double gz = -IMUAccess.currentAccelValues[2];
	/*
	previous roll, pitch calculations
	double roll = atan2(gy,gz);											//converts g-force into radians(roll)
	double pitch = atan2(-gx,(sqrt((gy)*(gy) + (gz)*(gz))));				//converts g-force into radians(pitch)
	double thrust = sqrt((gx)*(gx) + (gy)*(gy) + (gz)*(gz));				//magnitude of all forces (if stationary, should = 1)
	*/
	
	
	tRoll = atan2(gy,gz);				//converts g-force into radians(roll)
	tPitch = atan2(gx,gz);				//converts g-force into radians(pitch)
	//double thrust = sqrt((gx)*(gx) + (gy)*(gy) + (gz)*(gz));				//magnitude of all forces (if stationary, should = 1)
	
	
	
	
	tRoll *= 180.00;   tPitch *= 180.00;   //zAngle *= 180.00; 		converts radians into degrees
	tRoll /= 3.141592; tPitch /= 3.141592; //zAngle /= 3.141592;		converts radians into degrees
	
	if(tRoll > 0) tRoll -= 180;
	else if(tRoll < 0) tRoll += 180;
	
	if(tPitch > 0) tPitch -= 180;
	else if(tPitch < 0) tPitch += 180;
	
	//note, the small additions were calculated by averaging 500 samples on a surface with cellphone IMU activated
	//may need to be changed as  stuff moves around, would prefer a different system
	//tRoll = tRoll+ 5.6;
	//tPitch = tPitch+8.58;
}
double Accel_to_G(double Accel_Value,int axis)					
	{	
		/*
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
		*/
	}
void OrientationTwo::setupAngularPosition()
{
	double X_Change = 0.0; //initial rate at t = 0
	double y_Change = 0.0;
	double Z_Change = 0.0;
}
void OrientationTwo::updateAngularPosition(int dt)
{
	//NOTE: Flips X-Y axis and negates Z axis
	double X_Rate = currentGyroRates[0] = Gyro_to_degree(IMUAccess.currentGyroValues[1]);
	double Y_Rate = currentGyroRates[1] = Gyro_to_degree(IMUAccess.currentGyroValues[0]);
	double Z_Rate = currentGyroRates[2] = Gyro_to_degree(-IMUAccess.currentGyroValues[2]);
	
	
	/*
	Serial.print("X_RATE = "); Serial.print(X_Rate); Serial.print("\n");
	Serial.print("Y_RATE = "); Serial.print(X_Rate); Serial.print("\n");
	Serial.print("Z_RATE = "); Serial.print(X_Rate); Serial.print("\n");*/
	
	//to be used to help estimate change, will only be used in line directly above
	//may need to change X,Y,Z order depending on IMU
	//divide by a million because dt is in microseconds
	axisChange = {X_Rate*dt / 1000000., Y_Rate*dt / 1000000., Z_Rate*dt / 1000000.};

	X_angle += axisChange[0];
	Y_angle += axisChange[1];
	Z_angle += axisChange[2];
}
double Gyro_to_degree(double data_raw)
{
	double Sensitivity = 0.00875;
	double Change = data_raw*Sensitivity;
	return Change;
}
void OrientationTwo::updateKalman(int DT, double pitch, double pitchGyro, double roll, double rollGyro)
{
	if(prevKalmanCalculation == 0)
	{
		prevKalmanCalculation = micros();
	}
	float dt = DT / 1000000.;
	
	
	//Note: Pitch gets GyroRatesY because Y is the forward value here
	//Roll gets X because they are rotated
	currentKalmanPitch = pitchKalman.getAngle(pitch, pitchGyro,dt);
	currentKalmanRoll = rollKalman.getAngle(roll, rollGyro,dt);
}
void OrientationTwo::initializeKalman()
{
	updateOrientation();

	pitchKalman.setQangle(PITCH_Q_ANGLE);
	pitchKalman.setQbias(PITCH_Q_BIAS);
	pitchKalman.setRmeasure(PITCH_R_MEASURE);
	pitchKalman.setAngle(currentPitch);
	
	rollKalman.setQangle(ROLL_Q_ANGLE);
	rollKalman.setQbias(ROLL_Q_BIAS);
	rollKalman.setRmeasure(ROLL_R_MEASURE);
	rollKalman.setAngle(currentRoll);
	
	prevKalmanCalculation = 0;
}