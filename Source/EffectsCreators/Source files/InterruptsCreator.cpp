#include "InterruptsCreator.h"
#include "Configuration.h"

InterruptsCreator::InterruptsCreator(double frequency, double duration, int randomFactor, bool isActive) :EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->randomFactor.setValue(randomFactor);
}

InterruptsCreator::InterruptsCreator(Value frequency, Value duration, Value randomFactor, Value isActive) :EffectCreator(isActive)
{
	this->frequency.referTo(frequency);
	this->duration.referTo(duration);
	this->randomFactor.referTo(randomFactor);
}

float InterruptsCreator::createEffect(float signal)
{
	if (!(bool)isActive.getValue()||(float)frequency.getValue()==0||(float)duration.getValue()==0)
		return signal;
	if (play)
	{
		return 0;
	}
	else
	{
		return signal;
	}
}

void InterruptsCreator::moveTime()
{
	if (play)
	{
		durationTime++;
		if (durationTime >= (float)duration.getValue() * Configuration::getSampleRate())
		{
			durationTime = 0;
			play = false;
			freqTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * Configuration::getSampleRate()/100.0;
		}
	}
	else
	{
		freqTime++;
		if (freqTime >= 0.1 / (float)frequency.getValue() * Configuration::getSampleRate())
		{
			freqTime = 0;
			play = true;
			durationTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * Configuration::getSampleRate()/100.0;
		}
	}
}

void InterruptsCreator::setFrequency(Value frequency)
{
	this->frequency.referTo(frequency);
}

Value InterruptsCreator::getFrequency()
{
	return frequency;
}

void InterruptsCreator::setDuration(Value duration)
{
	this->duration.referTo(duration);
}

Value InterruptsCreator::getDuration()
{
	return duration;
}

void InterruptsCreator::setRandomFactor(Value randomFactor)
{
	this->randomFactor.referTo(randomFactor);
}

Value InterruptsCreator::getRandomFactor()
{
	return randomFactor;
}