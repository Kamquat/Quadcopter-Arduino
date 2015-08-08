/* Code heavily derived from
http://www.linushelgesson.se/2012/04/pitch-and-roll-estimating-kalman-filter-for-stabilizing-quadrocopters/
Thank you for the detailed explanation and example code
*/

#ifndef KALMAN_H
#define KALMAN_H

#include "Config.h"

class KalmanData
{
	public:
		float Q1,Q2,Q3,R1,R2;
		
		float x1,x2,x3;
		float p11,p12,p13,p21,p22,p23,p31,p32,p33;
		void innovateKalman(float,float,long);
		void initializeKalman(float, float, float, float, float);
		
	private:
};

#endif