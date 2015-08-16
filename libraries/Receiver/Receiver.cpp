#include "Arduino.h"
#include "Receiver.h"
#include "Wire.h"
#include "Config.h"

	void receiverChange1();
	void receiverChange2();
	void receiverChange3();
	void receiverChange4();
	void receiverChange5();
	void receiverChange6();
	void receiverChange7();
	void receiverChange8();
	void ReceiverTwo::setupReceiverPins()
	{
		for(int i = 0; i < 8; i++)
		{
			Receiver.channelWidth[i] = 0;
			Receiver.highTime[i] = 0;
		}
		pinMode(RECEIVER_PIN_1,INPUT);
		attachInterrupt(RECEIVER_PIN_1,receiverChange1,CHANGE);
		
		pinMode(RECEIVER_PIN_2,INPUT);
		attachInterrupt(RECEIVER_PIN_2,receiverChange2,CHANGE);
		
		pinMode(RECEIVER_PIN_3,INPUT);
		attachInterrupt(RECEIVER_PIN_3,receiverChange3,CHANGE);
		
		pinMode(RECEIVER_PIN_4,INPUT);
		attachInterrupt(RECEIVER_PIN_4,receiverChange4,CHANGE);
		
		pinMode(RECEIVER_PIN_5,INPUT);
		attachInterrupt(RECEIVER_PIN_5,receiverChange5,CHANGE);
		
		pinMode(RECEIVER_PIN_6,INPUT);
		attachInterrupt(RECEIVER_PIN_6,receiverChange6,CHANGE);
		
		pinMode(RECEIVER_PIN_7,INPUT);
		attachInterrupt(RECEIVER_PIN_7,receiverChange7,CHANGE);
		
		pinMode(RECEIVER_PIN_8,INPUT);
		attachInterrupt(RECEIVER_PIN_8,receiverChange8,CHANGE);
		
	}
	void ReceiverTwo::checkInputs()
	{
		for(int i =0; i < 8; i++)
		{
			if(channelWidth[i] > 2000) channelWidth[i] = 2000;
		}
	}
	void receiverChange1()
	{
		if(digitalRead(RECEIVER_PIN_1) == HIGH)
	  {
		Receiver.highTime[0] = micros();
	  }
	  else
	  {
		int time = micros();
		Receiver.channelWidth[0] = time - Receiver.highTime[0];
		Receiver.lastUpdated = time;
	  }
	}
	void receiverChange2()
	{
		if(digitalRead(RECEIVER_PIN_2) == HIGH)
	  {
		Receiver.highTime[1] = micros();
	  }
	  else
	  {
		int time = micros();
		Receiver.channelWidth[1] = time - Receiver.highTime[1];
		//Receiver.lastUpdated = time;
		
	  }
	}
	void receiverChange3()
	{
		if(digitalRead(RECEIVER_PIN_3) == HIGH)
	  {
		Receiver.highTime[2] = micros();
	  }
	  else
	  {
		int time = micros();
		Receiver.channelWidth[2] = time - Receiver.highTime[2];
		//Receiver.lastUpdated = time;
	  }
	}
	void receiverChange4()
	{
		if(digitalRead(RECEIVER_PIN_4) == HIGH)
	  {
		Receiver.highTime[3] = micros();
	  }
	  else
	  {
		int time = micros();
		Receiver.channelWidth[3] = time - Receiver.highTime[3];
		//Receiver.lastUpdated = time;
	  }
	}
	void receiverChange5()
	{
		if(digitalRead(RECEIVER_PIN_5) == HIGH)
	  {
		Receiver.highTime[4] = micros();
	  }
	  else
	  {
		int time = micros();
		Receiver.channelWidth[4] = time - Receiver.highTime[4];
		//Receiver.lastUpdated = time;
	  }
	}
	void receiverChange6()
	{
		if(digitalRead(RECEIVER_PIN_6) == HIGH)
	  {
		Receiver.highTime[5] = micros();
	  }
	  else
	  {
		int time = micros();
		Receiver.channelWidth[5] = time - Receiver.highTime[5];
		//Receiver.lastUpdated = time;
	  }
	}
	void receiverChange7()
	{
	if(digitalRead(RECEIVER_PIN_7) == HIGH)
	  {
		Receiver.highTime[6] = micros();
	  }
	  else
	  {
		int time = micros();
		Receiver.channelWidth[6] = time - Receiver.highTime[6];
		//Receiver.lastUpdated = time;
	  }
	}
	void receiverChange8()
	{
		if(digitalRead(RECEIVER_PIN_8) == HIGH)
		{
			Receiver.highTime[7] = micros();
		}
		else
		{
			int time = micros();
			Receiver.channelWidth[7] = time - Receiver.highTime[7];
			//Receiver.lastUpdated = time;
		}
	}

	