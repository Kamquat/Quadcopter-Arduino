#include <IMUAccess.h>
#include <Wire.h>
#include <Config.h>
#include <Receiver.h>

IMUAccessTwo IMUAccess;
ReceiverTwo Receiver;

int totalHz = 0;
int HzMicros = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
 
  IMUAccess.setupDevices();
  Receiver.setupReceiverPins();
  
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
  
  
  
  
  if(DEBUG==true)          {debugSerial();}
  if(DEBUG_TIMING == true) 
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
void debugSerial()
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
          Serial.print(Receiver.pulseLength[i]);
          Serial.print("uS\n");
        }
        Serial.print("\n\n\n");
        delay(2000);
      
}
void debugTimingSerial()
{
  /*   
  static int maxCount = 100;
  static int iterationCount = 0;
  static int myTime = 0;
  static int previousMicros = 0;
  iterationCount++;
  if (iterationCount == maxCount)
  {
    myTime = micros() - previousMicros;
    //myTime /= 1000000;
    Serial.print(maxCount);
    Serial.print(" rounds took: ");
    Serial.print(myTime);
    Serial.print(" micro-seconds \n");
  
    iterationCount = 0;
    delay(5000);
    previousMicros = micros();
  }*/
}
