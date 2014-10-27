#include <IMUAccess.h>
#include <Wire.h>
#include <Config.h>

IMUAccessTwo IMUAccess;


void setup()
{
  Serial.begin(9600);
  Wire.begin();
 
  IMUAccess.setupDevices();
  
  if (DEBUG == true) 
  {
    Serial.print("setup Complete\n");
  }
}
void loop()
{
  IMUAccess.updateIMUValues();
  

}
