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
	return signal + ((double)frequency.getValue()+(double)duration.getValue())*(double)volume.getValue()/100.0;
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