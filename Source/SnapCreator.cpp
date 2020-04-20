#include "SnapCreator.h"

SnapCreator::SnapCreator(double frequency, double duration, double volume, bool isActive) :EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->volume.setValue(volume);
}

SnapCreator::SnapCreator(Value frequency, Value duration, Value volume, Value isActive) :EffectCreator(isActive)
{
	this->frequency.referTo(frequency);
	this->duration.referTo(duration);
	this->volume.referTo(volume);
}

double SnapCreator::createEffect(double signal)
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
		if (durationTime % 882 != 0)
			return ((durationTime % 882)/-1764.0 + 0.5)*(float)volume.getValue()/100.0;
		else
		{
			return 1* (float)volume.getValue() / 100.0;
		}
	}
	return signal;
}

void SnapCreator::setFrequency(Value frequency)
{
	this->frequency.referTo(frequency);
}

Value SnapCreator::getFrequency()
{
	return frequency;
}

void SnapCreator::setDuration(Value duration)
{
	this->duration.referTo(duration);
}

Value SnapCreator::getDuration()
{
	return duration;
}

void SnapCreator::setVolume(Value volume)
{
	this->volume.referTo(volume);
}

Value SnapCreator::getVolume()
{
	return volume;
}