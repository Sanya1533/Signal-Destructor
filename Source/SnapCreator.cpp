#include "SnapCreator.h"

SnapCreator::SnapCreator(double frequency, double duration, double volume, int randomFactor, double snapDensity, double signalClipping, bool isActive) :EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->volume.setValue(volume);
	this->randomFactor.setValue(randomFactor);
	this->snapDensity.setValue(snapDensity);
	this->signalClipping.setValue(signalClipping);
}

SnapCreator::SnapCreator(Value frequency, Value duration, Value volume, Value randomFactor, Value snapDensity, Value signalClipping, Value isActive) :EffectCreator(isActive)
{
	this->frequency.referTo(frequency);
	this->duration.referTo(duration);
	this->volume.referTo(volume);
	this->randomFactor.referTo(randomFactor);
	this->snapDensity.referTo(snapDensity);
	this->signalClipping.referTo(signalClipping);
}

float SnapCreator::createEffect(float signal)
{
	if (!(bool)isActive.getValue())
		return signal;
	if (play)
	{
		int snapDist = (int)((float)duration.getValue() * 1 * 44100 / ((float)snapDensity.getValue() + 1));
		if (played < (float)snapDensity.getValue() && durationTime >= snapDist + played * snapDist)
		{
			if (direction)
				return (float)volume.getValue() / 100.0f;
			else
				return -(float)volume.getValue() / 100.0f;
		}
		else
		{
			return signal * (float)signalClipping.getValue();
		}
	}
	else
	{
		played = 0;
		return signal;
	}
	return signal;
}

void SnapCreator::moveTime()
{
	if (play)
	{
		durationTime++;
		int snapDist = (int)((float)duration.getValue() * 1 * 44100 / ((float)snapDensity.getValue() + 1));
		if ((durationTime - 1) >= snapDist + played * snapDist)
		{
			direction = !direction;
			played++;
		}
		if (durationTime >= (float)duration.getValue() * 1 * 44100)
		{
			durationTime = 0;
			played = 0;
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
			played = 0;
			durationTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * 441;
		}
	}
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

void SnapCreator::setRandomFactor(Value randomFactor)
{
	this->randomFactor.referTo(randomFactor);
}

Value SnapCreator::getRandomFactor()
{
	return randomFactor;
}

void SnapCreator::setDensity(Value snapDensity)
{
	this->snapDensity.referTo(snapDensity);
}

Value SnapCreator::getDensity()
{
	return snapDensity;
}

void SnapCreator::setSignalClipping(Value signalClipping)
{
	this->signalClipping.setValue(signalClipping);
}

Value SnapCreator::getSignalClipping()
{
	return signalClipping;
}
