#include "Configuration.h"

double Configuration::sampleRate = 44100.0;

double Configuration::getSampleRate()
{
	return sampleRate;
}

void Configuration::setSampleRate(double newRate)
{
	if (newRate > 0)
		sampleRate = newRate;
}
