#include <IMUAccess.h>
#include <Wire.h>


void setup() 
{
  Wire.begin();
  delay(15);
  Serial.begin(9600);
  IMUAccess.setupADXL345();
  IMUAccess.setupHMC5883L();
  //setupHMC5883L();

}

void loop() 
{
  IMUAccess.getAccelData();
  IMUAccess.getCompassData();
  delay(2000);  
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
int retrieveValue(int address, int secondAddress)
{
  /*
  Wire.beginTransmission(address);
    Wire.write(secondAddress); // register to read
    int value = Wire.endTransmission();
    if(value != 0)
    {
      Serial.print("failure on: ");
      Serial.print(secondAddress);
      Serial.print("due to endTransmission = ");
      Serial.print(value);
      Wire.endTransmission(true);
    }
    else
    {
      Serial.print("got a value:   ");
      Serial.print(secondAddress);
      Serial.print(" = ");
      Wire.requestFrom(address, 1); // read a byte
      Serial.print(Wire.read());
      Wire.endTransmission(true);
      //Serial.print(Wire.available());
    }
    Serial.print("\n");
    */
}
