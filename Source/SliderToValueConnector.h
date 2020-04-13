#pragma once
#include<JuceHeader.h>

template<typename T>
class SliderToValueConnector : public Slider::Listener
{
public:
	SliderToValueConnector(Value value);

	double getValue();

	void setValue(Value newValue);

	void setVariable(Value *varToChange);

	void setSourceSlider(Slider *slider);

	void sliderValueChanged(Slider *slider) override;

private:
 	Value *value=new Value();
};