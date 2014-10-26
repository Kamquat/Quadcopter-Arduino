#ifndef Config_h
#define Config_h



#define DEBUG true          //If set to true, will do debug work like Serial.print
#define DEBUG_TIMING false  //If set to true, include timing code


//Important value for calculating current acceleration value.
#define ACCEL_RESOLUTION 1    //0 = +-2g, 1 = +-4g, 2 = +- 8g, 3 = +-16g
#define ACCEL_FREQUENCY  12   //13 = 800Hz, 12 = 400Hz, 11 = 200Hz, and so on


//CTRL_REG 1----------------------
#define GYRO_DATA_RATE      3    //0 = 100Hz, 1 = 200Hz, 2 = 400Hz, 3 = 800Hz
#define GYRO_DATA_BANDWIDTH 0    //Has to do with "Cut-Off" See page 29/30

//CTRL_REG 4----------------------
#define GYRO_DATA_SCALE  0        //0 = 250dps, 01 = 500dps, 2 = 2000 dps
//NOTE MDPS based on GYRO_DATA_SCALE 0 = 8.75, 1 = 17.5, 2 = 70


//#define GYRO_RANGE     0         //

#endif