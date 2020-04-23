#include "NoiseCreator.h"

NoiseCreator::NoiseCreator(double frequency, double duration, double volume, double randomFactor,bool isActive):EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->volume.setValue(volume);
	this->randomFactor.setValue(randomFactor);
}

NoiseCreator::NoiseCreator(Value frequency, Value duration, Value volume, Value randomFactor, Value isActive):EffectCreator(isActive)
{
	this->frequency.referTo(frequency);
	this->duration.referTo(duration);
	this->volume.referTo(volume);
	this->randomFactor.referTo(randomFactor);
}

float NoiseCreator::createEffect(float signal)
{
	if (!(bool)isActive.getValue())
		return signal;
	if (play)
	{
		return rnd.nextFloat() * (float)volume.getValue() / 100.0;
	}
	else
	{
		return signal;
	}
	return signal;
}

void NoiseCreator::moveTime()
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

void NoiseCreator::setFrequency(Value frequency)
{
	this->frequency.referTo(frequency);
}

Value NoiseCreator::getFrequency()
{
	return frequency;
}

void NoiseCreator::setDuration(Value duration)
{
	this->duration.referTo(duration);
}

Value NoiseCreator::getDuration()
{
	return duration;
}

void NoiseCreator::setVolume(Value volume)
{
	this->volume.referTo(volume);
}

Value NoiseCreator::getVolume()
{
	return volume;
}

void NoiseCreator::setRandomFactor(Value randomFactor)
{
	this->randomFactor.referTo(randomFactor);
}

Value NoiseCreator::getRandomFactor()
{
	return randomFactor;
}
