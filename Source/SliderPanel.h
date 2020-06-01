#pragma once
#include <JuceHeader.h>
#include <vector>
#include "LabeledSlider.h"

using namespace std;

class SliderPanel :
	public Component,
	public Value::Listener
{
public:
	SliderPanel();
	~SliderPanel();

	enum ChildPosition
	{
		inFlexBox,
		upperLeftCorner,
		upperRightCorner,
		lowerLeftCorner,
		lowerRightCorner
	};

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

	void addComponent(Component* comp, ChildPosition position=ChildPosition::inFlexBox);

	String getTitle();

	Component* getChildByName(String title);

	float getCornerHeightFactor();

	void setCornerHeightFactor(float newFactor);

	void setActive(Value active);

private:
	Label* title;

	Value active = Value(true);

	Colour background;

	Colour borderColor;

	float borderWidth;

	Point<int> borderPosintion;

	FlexBox* flexBox;

	vector<pair<Component*, ChildPosition>> cornersComponents;
	
	float cornersHeightFactor = -1;

	// Óíàñëåäîâàíî ÷åðåç Listener
	virtual void valueChanged(Value& value) override;
};