#include "Arduino.h"
#include "MedianFilter.h"
#include "Config.h"

void MedianFilterTwo::setupFilter(int filterSize)
{
	previousValues = new double[filterSize];
	
	for(int i = 0; i< filterSize; i++)
	{
		previousValues[i] = 0;
	}
	
}
double MedianFilterTwo::filterInput(double newValue)
{
	
}