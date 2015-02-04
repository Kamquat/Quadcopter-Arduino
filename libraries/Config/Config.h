#ifndef Config_h
#define Config_h



#define DEBUG true         //If set to true, will do debug work like Serial.print
#define DEBUG_TIMING false  //If set to true, include timing code

//PIN VALUES===========================================================
#define RECEIVER_PIN_1 	22
#define RECEIVER_PIN_2	23
#define RECEIVER_PIN_3	24
#define RECEIVER_PIN_4	25
#define RECEIVER_PIN_5	26
#define RECEIVER_PIN_6	27
#define RECEIVER_PIN_7	28
#define RECEIVER_PIN_8	29

#define FRONT_MOTOR_PIN 6
#define BACK_MOTOR_PIN 7
#define LEFT_MOTOR_PIN 8
#define RIGHT_MOTOR_PIN 9

//RECEIVER VALUES==============================================================
#define RECEIVER_ROLL		0
#define RECEIVER_PITCH		1
#define RECEIVER_THROTTLE 	2
#define RECEIVER_YAW		3
#define RECEIVER_BUTTON1	4
#define RECEIVER_MODE		5
#define RECEIVER_BUTTON2	6
#define RECEIVER_KNOB1		7




//IMU VALUES================================================================
//Important value for calculating current acceleration value.
#define ACCEL_RESOLUTION 1    //0 = +-2g, 1 = +-4g, 2 = +- 8g, 3 = +-16g
#define ACCEL_FREQUENCY  10   //13 = 800Hz, 12 = 400Hz, 11 = 200Hz, 10 = 100Hz, 9 = 50Hz and so on
//THe code is not yet set up to average accel values. Might as well keep it at same frequency as ESC_SIGNAL_PERIOD


//CTRL_REG 1----------------------
#define GYRO_FREQUENCY      1    //0 = 100Hz, 1 = 200Hz, 2 = 400Hz, 3 = 800Hz
#define GYRO_DATA_BANDWIDTH 0    //Has to do with "Cut-Off" See page 29/30

//CTRL_REG 4----------------------
#define GYRO_DATA_SCALE  0        //0 = 250dps, 01 = 500dps, 2 = 2000 dps
//NOTE mDPS based on GYRO_DATA_SCALE 0 = 8.75, 1 = 17.5, 2 = 70

//#define GYRO_RANGE     0         //

#define COMPASS_FREQUENCY  			5      //3 =7.5Hz, 4 =15Hz, 5 =30Hz, 6 =75Hz
#define COMPASS_GAIN       			0      //see HMC datasheet page 13 0 = .73mG/LSb
#define COMPASS_SAMPLES_AVERAGED	3      //I Think this helps average the output values

#define RECALCULATE_MOTOR_PERIOD 1000000./100 //10,000 microseconds 100Hz

//PID VALUES=======================================================================
#define Pcorrection		1
#define Icorrection		0
#define Dcorrection		0


#endif