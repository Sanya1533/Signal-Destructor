#include "InterruptsCreator.h"

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

double InterruptsCreator::createEffect(double signal)
{
	if (!(bool)isActive.getValue())
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
	if (!play)
	{
		freqTime++;
		if (freqTime >= 0.1/(float)frequency.getValue() * 44100)
		{
			freqTime = 0;
			play = true;
			durationTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue()+1))*441;
		}
	}
	else
	{
		durationTime++;
		if (durationTime >= (float)duration.getValue() * 1 * 44100)
		{
			durationTime = 0;
			play = false;
			freqTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1))*441;
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