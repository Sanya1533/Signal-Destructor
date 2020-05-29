#include "HumCreator.h"
#include "maximilian.h"

HumCreator::HumCreator(double frequency, double duration, double volume, double randomFactor, bool isActive) :EffectCreator(Value(isActive))
{
	this->frequency.setValue(frequency);
	this->duration.setValue(duration);
	this->volume.setValue(volume);
	this->randomFactor.setValue(randomFactor);
}

HumCreator::HumCreator(Value frequency, Value duration, Value volume, Value randomFactor, Value isActive):EffectCreator(isActive)
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
		try
		{
			float x = (durationTime - 1) / 44100.0;
			previous = std::sin(x * 280);
			float ans = (std::sin(x * 280 * 120) * 0.4 + previous)*2.5f;
			if (ans > 1)
				ans = 1.0f;
			if (ans < -1)
				ans = -1.0f;
			return ans /2.5f* (float)volume.getValue() / 100.0;
			//float x = (durationTime - 1) / 44100.0;
			//previous = std::sin(x * 280) ;
			//float ans = std::sin(x * 280 * 120) * 0.4 + previous;
			//if (ans > 1)
			//	ans= 1.0f;
			//if (ans < 1)
			//	ans= -1.0f;
			//return ans*(float)volume.getValue()/100.0;
		}
		catch (const std::exception&)
		{
			return 1.0f;
		}
		//float cur = std::sin(x * 280) * (float)volume.getValue() / 100.0;
		//float noise = 0;
		//if (cur * previous <= 0&&counter<0)
		//{
		//	counter = 0;
		//}
		//if (counter >= 0 && counter < 44100 / 2)
		//{
		//	noise = (cur < 0 ? -1 : 1) * randomGenerator.nextFloat();
		//}
		//previous = cur;
		//float ans = cur + noise;
		//if (abs(ans) > 1)
		//	ans = 1;
		//return ans*(float)volume.getValue() / 100.0;
		//return std::sin(x*280+maxiLFO.sinewave((float)randomFactor.getValue())*8) * (float)volume.getValue() / 100.0+ (float)volume.getValue() / 50000.0*((randomGenerator.nextInt()%2==0)? ((randomGenerator.nextBool()?-1:1)* randomGenerator.nextFloat()):0);
		// AM - return std::sin(x * 200+maxiLFO.sinebuf(0.2f))* (float)volume.getValue() / 100.0;
		//return (80000 * x * x - 800 * x + 1) * (float)volume.getValue() / 100.0;
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
		if (counter >= 0)
			counter++;
		if (counter >= 44100 / 2)
			counter = -1;
		if (durationTime >= (float)duration.getValue() * 1 * 44100)
		{
			durationTime = 0;
			play = false;
			freqTime =0 /*randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * 441*/;
		}
	}
	else
	{
		freqTime++;
		if (freqTime >= 0.1 / (float)frequency.getValue() * 44100)
		{
			freqTime = 0;
			play = true;
			durationTime = 0/*randomGenerator.nextInt(Range<int>(-(int)randomFactor.getValue(), (int)randomFactor.getValue() + 1)) * 441*/;
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