#pragma once
#include <JuceHeader.h>
#include <vector>
#include "LabeledSlider.h"

using namespace std;

class SliderPanel :
	public Component,
	public MouseListener
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

	String getTitle();

	void mouseDoubleClick(const MouseEvent& event) override;

	class  MouseListener
	{
	public:
		void virtual mouseDoubleClick(SliderPanel* panel, const MouseEvent& event);
	};

	void addListener(SliderPanel::MouseListener* listener);

	void setActive(bool active);

	Value getActive();

	Component* getChildByName(String title);

private:
	Label* title;

	Value active = Value(true);

	Colour background;

	Colour borderColor;

	float borderWidth;

	Point<int> borderPosintion;

	FlexBox* flexBox;

	vector<SliderPanel::MouseListener*> listeners;// = vector<SliderPanel::MouseListener*>();
};