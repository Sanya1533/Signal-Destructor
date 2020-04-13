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
	return signal + ((double)frequency.getValue() + (double)duration.getValue()) * (double)volume.getValue() / 100.0;
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