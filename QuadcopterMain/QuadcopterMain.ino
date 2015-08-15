
/*NOTE: This code is for the Arduino Due board, it uses a
modified analogWrite frequency in the
Program Files (x86)\Arduino\hardware\arduino\sam\variants\arduino_due_x\variant.h
file
Change PWM_FREQUENCY from 1000 to 500. This change will update the motors at 500Hz,
be sure to limit the maximum thrust below full power, ex: 1950 and not 2000, or the esc may have trouble
reading the input. It does not seem to work for all pins, we use 6-9 for the motors*/


#include <IMUAccess.h>
#include <Wire.h>
#include <Config.h>
#include <Receiver.h>
#include <Orientation.h>
#include <FlightController.h>
#include <PID.h>
#include <Kalman.h>



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
#if DEBUG || DEBUG_TIMING
  Serial.begin(115200);
  Serial.println("Begin Setup");
#endif



#if DEBUG
  Serial.println("\tBegin Wire Setup");
#endif

  IMUAccess.clearI2CBus();
  //This clears the bus, handles issues with I2C hangs on startup

  Wire.begin();

  debugPrevTime = 0;

#if DEBUG
  Serial.println("\tBegin IMU Setup");
#endif

  IMUAccess.setupDevices();

#if DEBUG
  Serial.println("\tBegin Receiver Setup");
#endif

  Receiver.setupReceiverPins();

#if DEBUG
  Serial.println("\tBegin FlightController Setup");
#endif

  FlightController.setupMotors();

#if DEBUG
  Serial.println("\tBegin Orientation Setup");
#endif

  Orientation.setupOrientation();

#if DEBUG
  Serial.println("\tBegin PID Setup");
#endif

  PID.setupPID();

#if DEBUG
  Serial.println("\tEnd PID Setup");
#endif



  //NOTE: Small code tidbit to determine offset of accelerometer
  /*
  Serial.println("Begin AccelAveraging");
  long double pitchSum = 0;
  long double rollSum = 0;
  for(int i = 0; i <= 5000;i++)
  {
    IMUAccess.updateIMUValues();
    Orientation.updateOrientation(10000);
    pitchSum+= Orientation.tPitch;
    rollSum += Orientation.tRoll;
    delay(10);
    Serial.print(i); Serial.print("Pitch: "); Serial.print(Orientation.tPitch);
    Serial.print("Roll: "); Serial.println(Orientation.tRoll);
  }
  double pitchAverage = pitchSum / 5000.;
  double rollAverage = rollSum / 5000.;

  Serial.print("Accel pitch offset: ");
  Serial.println(pitchAverage);
  Serial.print("Accel roll offset: ");
  Serial.println(rollAverage);
  //this is an arming sequence to ensure quad waits before starting motors
  while(true);*/
#if CALIBRATE_ESC
  FlightController.calibrateESC();
#endif


#if ARMED
  #if DEBUG
    Serial.println("Awaiting Arming Sequence");
  #endif
    while (Receiver.channelWidth[RECEIVER_MODE] < 1700);
    delay(500);
    while (Receiver.channelWidth[RECEIVER_MODE] > 1200);
    delay(500);
    while (Receiver.channelWidth[RECEIVER_THROTTLE] > 1100);
    delay(500);
  
  #if DEBUG
    Serial.println("Arming Sequence Complete");
  #endif
#endif

#if DEBUG
  Serial.println("End Setup");
  HzMicros = micros();
#endif


}
void loop()
{
  //Reciever data collected automatically, see Receiver.cpp
  IMUAccess.updateIMUValues();
  FlightController.flightControl();






#if DEBUG
  debugSerial();
#endif
#if DEBUG_TIMING
  debugTimingSerial();
#endif
}
#if DEBUG
void debugSerial()
{
  int debugPeriod = 200000;
  if (micros() - debugPrevTime > debugPeriod)
  {
    Serial.println("\n\n");
    Serial.println("---------------------------------------------------");
    Serial.println("IMU Values:--------------------------------");
    Serial.println("Accelerometer Values:");
    Serial.print("X = "); Serial.println(IMUAccess.currentAccelValues[0]);
    Serial.print("Y = "); Serial.println(IMUAccess.currentAccelValues[1]);
    Serial.print("Z = "); Serial.println(IMUAccess.currentAccelValues[2]);


    Serial.println("Gyro Values:");
    Serial.print("X = "); Serial.println(IMUAccess.currentGyroValues[0]);
    Serial.print("Y = "); Serial.println(IMUAccess.currentGyroValues[1]);
    Serial.print("Z = "); Serial.println(IMUAccess.currentGyroValues[2]);


    Serial.println("\nCompass Values:");
    Serial.print("X = "); Serial.println(IMUAccess.currentCompassValues[0]);
    Serial.print("Y = "); Serial.println(IMUAccess.currentCompassValues[1]);
    Serial.print("Z = "); Serial.println(IMUAccess.currentCompassValues[2]);
    Serial.println("\n");

    Serial.println("Receiver Values :---------------------");
    for (int i = 0; i < 8; i++)
    {
      Serial.print("Channel ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.print(Receiver.channelWidth[i]);
      Serial.println("uS");
    }
    Serial.println("\n");
    Serial.println("Motor Powers-------------------");
#if !ARMED
    Serial.println("No signal given to motors");
#endif
    Serial.print("Receiver last updated: "); Serial.println(micros() - Receiver.lastUpdated);
    Serial.print("Flight Mode          : "); Serial.println(FlightController.flightMode);
    Serial.print("Front Left Motor     : "); Serial.println(FlightController.motorPower[0]);
    Serial.print("Front Right Motor    : "); Serial.println(FlightController.motorPower[1]);
    Serial.print("Back Left Motor      : "); Serial.println(FlightController.motorPower[2]);
    Serial.print("Back Right Motor     : "); Serial.println(FlightController.motorPower[3]);






    Serial.println("\n");
    Serial.println("Orientation Values:----------------------");
    Serial.print("\tRoll: "); Serial.println(Orientation.currentRoll);
    Serial.print("\tPitch: "); Serial.println(Orientation.currentPitch);
    Serial.println("");


    Serial.println("Gyro Values:--------------------");
    Serial.print("\tRoll: "); Serial.println(Orientation.currentGyroRates[0]);
    Serial.print("\tPitch: "); Serial.println(Orientation.currentGyroRates[1]);
    Serial.print("\tYaw: "); Serial.println(Orientation.currentGyroRates[2]);
    Serial.println("");

    /*
    Serial.println("Kalman Values:-----------------");
    Serial.print("\tRoll: "); Serial.println(Orientation.currentKalmanRoll);
    Serial.print("\tPitch: "); Serial.println(Orientation.currentKalmanPitch);
    Serial.println("");
    */
    
    
    Serial.println("PIDadjustments--------------");
    Serial.print("Pitch adjustment: "); Serial.println(PID.pitchAdjustment);
    Serial.print("Roll adjustment: "); Serial.println(PID.rollAdjustment);
    Serial.print("Yaw adjustment: "); Serial.println(PID.yawAdjustment);
    /*
    Serial.println("Angle from Gyro:---------------------");
    Serial.print("\tX_Angle: "); Serial.println(Orientation.X_angle);
    Serial.print("\ty_Angle: "); Serial.println(Orientation.Y_angle);
    Serial.print("\tZ_Angle: "); Serial.println(Orientation.Z_angle);
    */
    
    debugPrevTime = micros();
  }

}
#endif
#if DEBUG_TIMING
void debugTimingSerial()
{
  {
    if (micros() - HzMicros > 1 * 1000000)
    {
      Serial.print("repeated "); Serial.print(totalHz); Serial.print(" times that second\n");
      Serial.print("HzMicros = "); Serial.print(micros() - HzMicros); Serial.print("\n");
      totalHz = 0;
      delay(500);
      HzMicros = micros();
    }
    //debugTimingSerial();
    totalHz++;
  }
}
#endif
