#include "InterruptsCreator.h"

InterruptsCreator::InterruptsCreator(double frequency, double duration, double density, bool isActive) :EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->density.setValue(density);
}

InterruptsCreator::InterruptsCreator(Value frequency, Value duration, Value density, Value isActive) :EffectCreator(isActive)
{
	this->frequency.referTo(frequency);
	this->duration.referTo(duration);
	this->density.referTo(density);
}

double InterruptsCreator::createEffect(double signal)
{
	if (!(bool)isActive.getValue())
		return signal;
	return signal + ((double)frequency.getValue() + (double)duration.getValue()) * (double)density.getValue() / 100.0;
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

void InterruptsCreator::setDensity(Value density)
{
	this->density.referTo(density);
}

Value InterruptsCreator::getDensity()
{
	return density;
}