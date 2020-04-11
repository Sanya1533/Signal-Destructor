#pragma once
#include <JuceHeader.h>
#include <vector>
#include "SliderListener.h"
#include "LabeledSlider.h"

using namespace std;

class SliderPanel :
	public Component,
	public SliderListener
{
public:
	SliderPanel();
	~SliderPanel();

	void paint(Graphics&) override;

	void resized() override;

	void setBackgroundColor(juce::Colour color);

	void setBorderColour(juce::Colour color);

	void setBorderWidth(float width);

	void setBorderPosition(Point<int> posintion);

	void setTitle(Label* label);

	void setTitle(String text);

	void setFlexBox(FlexBox* flexBox);

	FlexBox* getFlexBox();

	void addComponent(LabeledSlider* comp);

	void addListener(SliderListener* listener);

	void sliderValueChanged(Slider* slider, String  message) override;

	String getTitle();

private:
	Label* title;

	Colour background;

	Colour borderColor;

	float borderWidth;

	Point<int> borderPosintion;

	FlexBox* flexBox;

	vector<SliderListener*> listeners = vector<SliderListener*>();
};