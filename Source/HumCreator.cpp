#include "HumCreator.h"

HumCreator::HumCreator(double frequency, double duration, double volume, double randomFactor, bool isActive) :EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->volume.setValue(volume);
	this->randomFactor.setValue(randomFactor);
}

HumCreator::HumCreator(Value frequency, Value duration, Value volume, Value randomFactor, Value isActive) :EffectCreator(isActive)
{
	this->frequency.referTo(frequency);
	this->duration.referTo(duration);
	this->volume.referTo(volume);
	this->randomFactor.referTo(randomFactor);
}

float HumCreator::createEffect(float signal)
{
	if (!(bool)isActive.getValue())
		return signal;
	if (play)
	{
		float x =((durationTime - 1) % 441) / 44100.0;
		return (80000 * x * x - 800 * x + 1) * (float)volume.getValue() / 100.0;
	}
	else
	{
		return signal;
	}
	return signal;
}

void HumCreator::moveTime()
{
	if (play)
	{
		durationTime++;
		if (durationTime >= (float)duration.getValue() * 1 * 44100)
		{
			durationTime = 0;
			play = false;
			freqTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * 441;
		}
	}
	else
	{
		freqTime++;
		if (freqTime >= 0.1 / (float)frequency.getValue() * 44100)
		{
			freqTime = 0;
			play = true;
			durationTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * 441;
		}
	}
}

void HumCreator::setFrequency(Value frequency)
{
	this->frequency.referTo(frequency);
}

Value HumCreator::getFrequency()
{
	return frequency;
}

void HumCreator::setDuration(Value duration)
{
	this->duration.referTo(duration);
}

Value HumCreator::getDuration()
{
	return duration;
}

void HumCreator::setVolume(Value volume)
{
	this->volume.referTo(volume);
}

Value HumCreator::getVolume()
{
	return volume;
}

void HumCreator::setRandomFactor(Value randomFactor)
{
	this->randomFactor.referTo(randomFactor);
}

Value HumCreator::getRandomFactor()
{
	return 	randomFactor;
}
