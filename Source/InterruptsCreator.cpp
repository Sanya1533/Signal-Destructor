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
	if (!(bool)isActive.getValue() || (float)frequency.getValue() == 0)
		return signal;
	if (!play)
	{
		freqTime++;
		if (freqTime/2.0 >= 0.2 / (float)frequency.getValue() * 44100)
		{
			freqTime = 0;
			play = true;
		}
		return signal;
	}
	else
	{
		durationTime++;
		if (durationTime/2.0 >= 5*(float)duration.getValue() * 44100)
		{
			durationTime = 0;
			played = 0;
			play = false;
			return signal;
		}
		int samplesToPlay = (float)duration.getValue() * 5 * 44100 / 100 * (float)density.getValue();
		int rast = (float)duration.getValue() * 5 * 44100 / (samplesToPlay + 1);
		if (durationTime % rast == 0)
		{
			if (played < samplesToPlay)
			{
				played++;
				b = !b;
				return b?0.1:-0.1;
			}
		}
		else
		{
			if (((float)duration.getValue() * 5 * 44100 - durationTime) / rast > played)
			{
				if (played < samplesToPlay)
				{
					played++;
					b = !b;
					return b ? 0.1 : -0.1;
				}
			}
		}
	}
	return signal;
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