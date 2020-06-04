#include "HumCreator.h"
#include "maximilian.h"
#include "Configuration.h"

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
		if (false)
		{
			//first way
			float x = (durationTime - 1) / Configuration::getSampleRate();
			float d = /*maxiLFO.sinewave(30.0f) **/ 0.1;
			float ans = (std::sin(x * 280 * 120 * d) * 0.4 + std::sin(x * 280 * d));
			return ans * (float)volume.getValue() / 100.0;
		}
		else
		{
			//second way
			float x = (durationTime - 1) / Configuration::getSampleRate();
			float ans = (std::sin(x * 280 * 120) * 0.4 + std::sin(x * 280)) * 15.0f;
			if (ans > 1)
				ans = 1.0f;
			if (ans < -1)
				ans = -1.0f;
			return ans / 15.0f * (float)volume.getValue() / 100.0;
		}
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
		if (durationTime >= (float)duration.getValue()*Configuration::getSampleRate())
		{
			durationTime = 0;
			play = false;
			freqTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * Configuration::getSampleRate()/100.0;
		}
	}
	else
	{
		freqTime++;
		if (freqTime >= 0.1 / (float)frequency.getValue() * Configuration::getSampleRate())
		{
			freqTime = 0;
			play = true;
			durationTime = randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * Configuration::getSampleRate()/100.0;
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