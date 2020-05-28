#include "LabeledSlider.h"

using namespace std;

LabeledSlider::LabeledSlider()
{
	this->slider = new Slider();
	this->label = new Label("", "place your text here");
	this->labelPercentage = 0.1;
	this->labelPosition = LabelPosition::LabelAbove;
	addAndMakeVisible(slider);
	addAndMakeVisible(label);
}

LabeledSlider::LabeledSlider(Slider* slider, Label* label, LabelPosition labelPosition, float labelPercentage)
{
	this->slider = slider;
	this->label = label;
	this->labelPosition = labelPosition;
	this->labelPercentage = labelPercentage;
	addAndMakeVisible(this->slider);
	addAndMakeVisible(this->label);
}

LabeledSlider::~LabeledSlider()
{
}

void LabeledSlider::paint(Graphics& g)
{
}

void LabeledSlider::resized()
{
	switch (labelPosition)
	{
	case LabelPosition::LabelAbove:
		if (isSliderRotary())
			label->setBounds(max(0, (getWidth() - getHeight()) / 2), 0, getWidth(), getHeight() * labelPercentage);
		else
			label->setBounds(0, 0, getWidth(), getHeight() * labelPercentage);
		slider->setBounds(0, label->getHeight(), getWidth(), getHeight() - label->getHeight());
		break;
	case LabelPosition::LabelBelow:
		if (isSliderRotary())
			label->setBounds(max(0, (getWidth() - getHeight()) / 2), getHeight() * (1 - labelPercentage), getWidth(), getHeight() * labelPercentage);
		else
			label->setBounds(0, getHeight() * (1 - labelPercentage), getWidth(), getHeight() * labelPercentage);
		slider->setBounds(0, 0, getWidth(), getHeight() - label->getHeight());
		break;
	case LabelPosition::LabelLeft:
		label->setBounds(0, (getHeight() - label->getHeight()) / 2, getWidth() * labelPercentage, label->getHeight());
		slider->setBounds(label->getWidth(), 0, getWidth() - label->getWidth(), getHeight());
		break;
	case LabelPosition::LabelRight:
		label->setBounds(getWidth() * (1 - labelPercentage), (getHeight() - label->getHeight()) / 2, getWidth() * labelPercentage, label->getHeight());
		slider->setBounds(0, 0, getWidth() - label->getWidth(), getHeight());
		break;
	default:
		slider->setBounds(getBounds());
		break;
	}
}

void LabeledSlider::setLabelPosition(LabelPosition position)
{
	this->labelPosition = position;
}

void LabeledSlider::setLabelPercentage(float percantage)
{
	labelPercentage = percantage;
}

void LabeledSlider::setLabel(Label* label)
{
	this->label = label;
}

void LabeledSlider::setSlider(Slider* slider)
{
	this->slider = slider;
}

Slider* LabeledSlider::getSlider()
{
	return slider;
}

void LabeledSlider::setText(String text)
{
	this->label->setText(text, dontSendNotification);
}

void LabeledSlider::setFont(Font font)
{
	this->label->setFont(font);
}

void LabeledSlider::setSliderStyle(Slider::SliderStyle sliderStyle)
{
	this->slider->setSliderStyle(sliderStyle);
}

Label* LabeledSlider::getLabel()
{
	return label;
}

void LabeledSlider::setMaxValue(double newMaxValue)
{
	slider->setRange(slider->getMinValue(),newMaxValue, slider->getInterval());
}

void LabeledSlider::setMinValue(double newMinValue)
{
	slider->setRange(newMinValue,slider->getMaxValue(),slider->getInterval());
}

void LabeledSlider::setInterval(double newInterval)
{
	slider->setRange(slider->getMinValue(), slider->getMaxValue(), newInterval);
}

void LabeledSlider::setRange(double newMinValue, double newMaxValue, double newInterval)
{
	if (newMinValue == NULL)
		newMinValue = slider->getMinValue();
	if (newMaxValue == NULL)
		newMaxValue = slider->getMaxValue();
	if (newInterval == NULL)
		newInterval = slider->getInterval();
	slider->setRange(newMinValue,newMaxValue,newInterval);
}

bool LabeledSlider::isSliderRotary()
{
	return this->slider->getSliderStyle() == Slider::SliderStyle::Rotary ||
		this->slider->getSliderStyle() == Slider::SliderStyle::RotaryHorizontalDrag ||
		this->slider->getSliderStyle() == Slider::SliderStyle::RotaryHorizontalVerticalDrag ||
		this->slider->getSliderStyle() == Slider::SliderStyle::RotaryVerticalDrag;
}