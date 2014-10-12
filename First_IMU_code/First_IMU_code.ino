#include <IMUAccess.h>
#include <Wire.h>


void setup() 
{
  Wire.begin();
  Serial.begin(9600);
  //IMUAccess.setupHMC();

}

void loop() 
{
  retrieveValue(HMC5883L_ADDRESS, HMC5883L_DATA_X0);
  retrieveValue(HMC5883L_ADDRESS, HMC5883L_DATA_X1);
  retrieveValue(HMC5883L_ADDRESS, HMC5883L_DATA_Y0);
  retrieveValue(HMC5883L_ADDRESS, HMC5883L_DATA_Y1);
  retrieveValue(HMC5883L_ADDRESS, HMC5883L_DATA_Z0);
  retrieveValue(HMC5883L_ADDRESS, HMC5883L_DATA_Z1);
  //retrieveValue(HMC5883L_ADDRESS, HMC5883L_DATA_Z1);
  delay(1000);  
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
int retrieveValue(int address, int secondAddress)
{
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
}
