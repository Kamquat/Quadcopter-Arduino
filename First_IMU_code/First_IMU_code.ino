#include <IMUAccess.h>
#include <Wire.h>
#include <Config.h>

int i = 0;
int previousMicros = 0;
double myTime = 0;
void setup()
{
  Wire.begin();
  delay(15);
  Serial.begin(9600);
  IMUAccess.setupADXL345();
  IMUAccess.setupHMC5883L();
  //setupHMC5883L();
  if (DEBUG_VALUES == true) 
  {
    previousMicros = micros();
  }

}

void loop()
{
  i++;
  IMUAccess.getAccelData();
  IMUAccess.getCompassData();
  //delay(2000);
  //Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  if (DEBUG_TIMING == true)
  {
    if (i == 100)
    {
      myTime = micros() - previousMicros;
      myTime /= 1000000;
      Serial.print("100 rounds took: ");
      Serial.print(myTime);
      Serial.print(" seconds \n");

      i = 0;
      delay(5000);
      previousMicros = micros();
    }
  }
}
