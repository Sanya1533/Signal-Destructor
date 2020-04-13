#include "NoiseCreator.h"

NoiseCreator::NoiseCreator(double frequency, double duration, double volume, bool isActive):EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->volume.setValue(volume);
}

NoiseCreator::NoiseCreator(Value frequency, Value duration, Value volume, Value isActive):EffectCreator(isActive)
{
	this->frequency.referTo(frequency);
	this->duration.referTo(duration);
	this->volume.referTo(volume);
}

double NoiseCreator::createEffect(double signal)
{
	if (!(bool)isActive.getValue())
		return signal;
	return signal + ((double)frequency.getValue() + (double)duration.getValue()) * (double)volume.getValue() / 100.0;
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