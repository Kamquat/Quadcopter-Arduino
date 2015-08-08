/* code heavily derived from
http://www.linushelgesson.se/2012/04/pitch-and-roll-estimating-kalman-filter-for-stabilizing-quadrocopters/
Thank you for the detailed explanation and example code
*/

#include "Kalman.h"


void KalmanData::initializeKalman(float q1, float q2, float q3, float r1, float r2)
{
	x1 = 0; x2 = 0; x3 = 0;
	
	p11 = 1000; p12 = 0; p13 = 0;
	p21 = 0; p22 = 1000; p23 = 0;
	p31 = 0; p32 = 0; p33 = 1000;
	
	Q1 = q1; Q2 = q2; Q3 = q3;
	R1 = r1; R2 = r2;

}
void KalmanData::innovateKalman(float z1,float z2,float dt)
{
	float y1, y2;
	float a, b, c;
	float sDet;
	float s11, s12, s21, s22;
	float k11, k12, k21, k22, k31, k32;
	float tp11, tp12, tp13, tp21, tp22, tp23, tp31, tp32, tp33;
	
	
	
	//Step 1
	// x(k) = Fx(k-1) + Bu + w:
	x1 = x1 + dt * (x2 - x3);
	//x2 = x2;
	//x3 = x3;

	//Step 2
	// P = FPF'+Q
	a = p11 + dt * ( p21 - p31);
	b = p12 + dt * (p22 - p32);
	c = p13 + dt * (p23 - p33);
	p11 = a + dt * (b - c) + Q1;
	p12 = b;
	p13 = c;
	p21 = p21 + dt * (p22 - p23);
	p22 = p22 + Q2;
	//p23 = p23;
	p31 = p31 + dt * (p32 - p33);
	//p32 = p32;
	p33 = p33 + Q3;
	
	//Step 3
	// y = z(k) - Hx(k)
	y1 = z1 - x1;
	y2 = z2 - x2;
	
	//Step 4
	// S = HPT' + R
	s11 = p11 + R1;
	s12 = p12;
	s21 = p21;
	s22 = p22 + R2;
	
	//Step 5
	// K = PH*inv(S)
	sDet = 1/(s11*s22 - s12*s21);
	k11 = (p11*s22 - p12*s21)*sDet;
	k12 = (p12*s11 - p11*s12)*sDet;
	k21 = (p21*s22 - p22*s21)*sDet;
	k22 = (p22*s11 - p21*s12)*sDet;
	k31 = (p31*s22 - p32*s21)*sDet;
	k32 = (p32*s11 - p31*s12)*sDet;
	
	// Step 6
	// x = x + Ky
	
	x1 = x1 + k11*y1 + k12*y2;
	x2 = x2 + k21*y1 + k22*y2;
	x3 = x3 + k31*y1 + k32*y2;
	
	// Step 7
	// P = (I-KH)P
	tp11 = p11*(1.0f - k11) - p21*k12;
	tp12 = p12*(1.0f - k11) - p22*k12;
	tp13 = p13*(1.0f - k11) - p23*k12;
	tp21 = p21*(1.0f - k22) - p11*k21;
	tp22 = p22*(1.0f - k22) - p12*k21;
	tp23 = p23*(1.0f - k22) - p13*k21;
	tp31 = p31 - p21*k32 - p11*k31;
	tp32 = p32 - p22*k32 - p12*k31;
	tp33 = p33 - p22*k32 - p13*k31;
	p11 = tp11; p12 = tp12; p13 = tp13;
	p21 = tp21; p22 = tp22; p23 = tp23;
	p31 = tp31; p32 = tp32; p33 = tp33;
}