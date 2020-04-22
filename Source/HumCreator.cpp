#include "HumCreator.h"

HumCreator::HumCreator(double frequency, double duration, double volume, bool isActive) :EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->volume.setValue(volume);
}

HumCreator::HumCreator(Value frequency, Value duration, Value volume, Value isActive) :EffectCreator(isActive)
{
	this->frequency.referTo(frequency);
	this->duration.referTo(duration);
	this->volume.referTo(volume);
}

double HumCreator::createEffect(double signal)
{
	if (!(bool)isActive.getValue())
		return signal;
	if (!play)
	{
		freqTime++;
		if (freqTime / 2.0 >= 0.2 / (float)frequency.getValue() * 44100)
		{
			freqTime = 0;
			play = true;
		}
		return signal;
	}
	else
	{
		durationTime++;
		if (durationTime / 2.0 >= 5 * (float)duration.getValue() * 44100)
		{
			durationTime = 0;
			play = false;
			return signal;
		}
		int x1 = (durationTime-1) % 441;
		float x = x1 / 44100.0;
		return (80000*x*x-800*x+1)*(float)volume.getValue()/100.0;
	}
	return signal;
}

void HumCreator::moveTime()
{
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