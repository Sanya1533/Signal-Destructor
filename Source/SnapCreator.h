#pragma once
#include "EffectCreator.h"

class SnapCreator : public EffectCreator
{
public:
	SnapCreator(double frequency = 0.0, double duration = 0.0, double volume = 0.0, bool isActive = true);

	SnapCreator(Value frequency = Value(0.0), Value duration = Value(0.0), Value volume = Value(0.0), Value isActive = Value(true));

	double createEffect(double signal) override;

	void moveTime() override;

	void setFrequency(Value frequency);
	Value getFrequency();

	void setDuration(Value duration);
	Value getDuration();

	void setVolume(Value volume);
	Value getVolume();

private:
	Value frequency;

	Value duration;

	Value volume;

	int durationTime = 0;

	int freqTime = 0;

	bool play = false;
};