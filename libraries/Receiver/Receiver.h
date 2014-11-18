/*
  Receiver.h Library for a quadcopter project.
  Created by Samuel L. B., October 11, 2014.
  Released into the public domain.

  This library  will read values from the remote receiver and
  convert it into... something...I guess

*/


#ifndef Receiver_h
#define Receiver_h

//void setupReceiverPins();



#include "Arduino.h"


class ReceiverTwo
{
	public:
		void setupReceiverPins();
		volatile int channelWidth[8];
		volatile int highTime[8];

};
extern ReceiverTwo Receiver;







#endif