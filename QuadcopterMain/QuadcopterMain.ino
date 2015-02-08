
/*NOTE: This code is for the Arduino Due board, it uses a 
modified analogWrite frequency in the
Program Files (x86)\Arduino\hardware\arduino\sam\variants\arduino_due_x\variant.h
file
Change PWM_FREQUENCY from 1000 to 500. This change will update the motors at 500Hz,
be sure to limit the maximum thrust below full powerex: 1950 and not 2000, or the esc may have trouble
reading the input. It does not seem to work for all pins, we use 6-9 for the motors*/


#include <IMUAccess.h>
#include <Wire.h>
#include <Config.h>
#include <Receiver.h>
#include <Orientation.h>
#include <FlightController.h>
#include <PID.h>



OrientationTwo Orientation;
IMUAccessTwo IMUAccess;
ReceiverTwo Receiver;
FlightControllerTwo FlightController;
PIDTwo PID;
int debugPrevTime;

int totalHz = 0;
int HzMicros = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  debugPrevTime= 0;
  
  IMUAccess.setupDevices();
  Receiver.setupReceiverPins();
  FlightController.setupMotors();
  Orientation.setupOrientation();
  PID.setupPID();
  
  if (DEBUG == true) 
  {
    Serial.print("setup Complete\n");
    HzMicros = micros();
    
  }
}
void loop()
{
  //Reciever data collected automatically, see Receiver.cpp
  IMUAccess.updateIMUValues();
  FlightController.flightControl();
  
  
  
  
  
  
  if(DEBUG==true)          
  {
    debugSerial();
  }
  if(DEBUG_TIMING == true) {debugTimingSerial();}
}
void debugSerial()
{
      int debugPeriod = 2000000;
      if(micros()-debugPrevTime > debugPeriod)
      {
        Serial.print("IMU Values:\n");
        Serial.print("\nAccelerometer Values:");
  	Serial.print("\nX = "); Serial.print(IMUAccess.currentAccelValues[0]);
  	Serial.print("\nY = "); Serial.print(IMUAccess.currentAccelValues[1]);
  	Serial.print("\nZ = "); Serial.print(IMUAccess.currentAccelValues[2]);
  	
  		
  	Serial.print("\nGyro Values:");
  	Serial.print("\nX = "); Serial.print(IMUAccess.currentGyroValues[0]);
  	Serial.print("\nY = "); Serial.print(IMUAccess.currentGyroValues[1]);
  	Serial.print("\nZ = "); Serial.print(IMUAccess.currentGyroValues[2]);
  	
  		
  	Serial.print("\nCompass Values:");
  	Serial.print("\nX = "); Serial.print(IMUAccess.currentCompassValues[0]);
  	Serial.print("\nY = "); Serial.print(IMUAccess.currentCompassValues[1]);
  	Serial.print("\nZ = "); Serial.print(IMUAccess.currentCompassValues[2]);
        Serial.print("\n\n\n");
      
        Serial.print("Receiver Values : \n");
        for(int i = 0; i < 8; i++)
        {
            Serial.print("Channel "); 
            Serial.print(i); 
            Serial.print(" = "); 
            Serial.print(Receiver.channelWidth[i]);
            Serial.print("uS\n");
        }
        Serial.print("\n\n\n");
        Serial.print("Orientation Values:\n");
	Serial.print("Roll: "); Serial.print(Orientation.currentOrientation[0]);
	Serial.print("\t");
	Serial.print("Pitch: "); Serial.print(Orientation.currentOrientation[1]);
	Serial.print("\t");
	Serial.print("Thrust: "); Serial.print(Orientation.currentOrientation[2]);
	Serial.print("\n");
  
        Serial.print("\n\n\n");
        Serial.print("Angle from Gyro:\n");
	Serial.print("X_Angle: "); Serial.print(Orientation.X_angle);
	Serial.print("\t");
	Serial.print("y_Angle: "); Serial.print(Orientation.Y_angle);
	Serial.print("\t");
	Serial.print("Z_Angle: "); Serial.print(Orientation.Z_angle);
	Serial.print("\n");
        
        
        Serial.print("\n\n\n");
        //delay(2000);
        debugPrevTime = micros();
      }
      
}
void debugTimingSerial()
{
  {
    if(micros()-HzMicros > 1 * 1000000)
    {
      Serial.print("repeated "); Serial.print(totalHz); Serial.print(" times that second\n");
       Serial.print("HzMicros = "); Serial.print(micros()-HzMicros); Serial.print("\n"); 
      totalHz = 0;
      delay(500);
      HzMicros = micros();
    }
    //debugTimingSerial();
    totalHz++;
  }  
}
