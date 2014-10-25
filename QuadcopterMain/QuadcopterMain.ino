#include <IMUAccess.h>
#include <Wire.h>
#include <Config.h>

int i = 0;
int previousMicros = 0;
double myTime = 0;
void setup()
{
  Serial.begin(9600);
  
  Wire.begin();
  delay(15);
  
  IMUAccess.setupDevices();
  
  if (DEBUG == true) 
  {
    Serial.print("setup Complete");
    previousMicros = micros();
  }

}
void loop()
{
  IMUAccess.updateIMUValues();
}
