#ifndef Config_h
#define Config_h


#define ARMED 			false
#define DEBUG 			true         //If set to true, will do debug work like Serial.print
#define CALIBRATE_ESC 	false
#define DEBUG_TIMING 	false  //If set to true, include timing code

//PIN VALUES===========================================================
#define RECEIVER_PIN_1 	31
#define RECEIVER_PIN_2	33
#define RECEIVER_PIN_3	35
#define RECEIVER_PIN_4	37
#define RECEIVER_PIN_5	39
#define RECEIVER_PIN_6	41
#define RECEIVER_PIN_7	43
#define RECEIVER_PIN_8	45


/*
The following arm configuration assumes the two red legs make up the front end
the two white legs make up the back end

X - Red
+ - White

top view
frontLeft    FrontRight
X           X



-           -
BackLeft     BackRight

Recall motors should be on these pins due to differences in analogWrite frequencies
*/
#define FRONT_LEFT_MOTOR_PIN 6
#define FRONT_RIGHT_MOTOR_PIN 7
#define BACK_LEFT_MOTOR_PIN 8
#define BACK_RIGHT_MOTOR_PIN 9

//RECEIVER VALUES==============================================================
#define RECEIVER_ROLL		0
#define RECEIVER_PITCH		1
#define RECEIVER_THROTTLE 	2
#define RECEIVER_YAW		3
#define RECEIVER_BUTTON1	4
#define RECEIVER_MODE		5
#define RECEIVER_BUTTON2	6
#define RECEIVER_KNOB1		7


//Other init. values
#define GYRO_INIT_SAMPLES 2000.
#define ACCEL_INIT_SAMPLES 2000.



//IMU VALUES================================================================
//Important value for calculating current acceleration value.
#define ACCEL_RESOLUTION 1    //0 = +-2g, 1 = +-4g, 2 = +- 8g, 3 = +-16g
#define ACCEL_FREQUENCY  10   //13 = 800Hz, 12 = 400Hz, 11 = 200Hz, 10 = 100Hz, 9 = 50Hz and so on
//THe code is not yet set up to average accel values. Might as well keep it at same frequency as ESC_SIGNAL_PERIOD


//CTRL_REG 1----------------------
#define GYRO_FREQUENCY      1    //0 = 100Hz, 1 = 200Hz, 2 = 400Hz, 3 = 800Hz
#define GYRO_DATA_BANDWIDTH 0    //Has to do with "Cut-Off" See page 29/30

//CTRL_REG 4----------------------
#define GYRO_DATA_SCALE  0        //0 = 8.75mdps/digit, 01 = 17.5mdps/digit, 2 = 70mdps/digit
//NOTE mDPS based on GYRO_DATA_SCALE 0 = 8.75, 1 = 17.5, 2 = 70

//#define GYRO_RANGE     0         //

#define COMPASS_FREQUENCY  			5      //3 =7.5Hz, 4 =15Hz, 5 =30Hz, 6 =75Hz
#define COMPASS_GAIN       			0      //see HMC datasheet page 13 0 = .73mG/LSb
#define COMPASS_SAMPLES_AVERAGED	3      //I Think this helps average the output values

#define RECALCULATE_MOTOR_PERIOD 1000000./400 //10,00 microseconds 400Hz

//PID VALUES=======================================================================
#define P_PITCH_ANGLE		1
#define I_PITCH_ANGLE		0
#define D_PITCH_ANGLE		0

#define P_ROLL_ANGLE		1
#define I_ROLL_ANGLE		0
#define D_ROLL_ANGLE		0

#define P_PITCH_RATE		1
#define I_PITCH_RATE		0
#define D_PITCH_RATE		0

#define P_ROLL_RATE			1
#define I_ROLL_RATE			0
#define D_ROLL_RATE			0

#define P_YAW_RATE			1
#define I_YAW_RATE			0
#define D_YAW_RATE			0

#define PITCH_ANGLE_MAX_CUM	100
#define ROLL_ANGLE_MAX_CUM	100
#define PITCH_RATE_MAX_CUM	100
#define ROLL_RATE_MAX_CUM	100
#define YAW_RATE_MAX_CUM	100


//---KALMAN FILTER VALUES
#define PITCH_Q_ANGLE 		.001
#define PITCH_Q_BIAS 		.003
#define PITCH_R_MEASURE		.003

#define ROLL_Q_ANGLE 		.001
#define ROLL_Q_BIAS 		.003
#define ROLL_R_MEASURE		.003


#endif