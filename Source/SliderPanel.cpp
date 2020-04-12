#include "SliderPanel.h"
#include "SliderListener.h"
#include "LabeledSlider.h"

SliderPanel::SliderPanel()
{
	title = new Label();
	title->setBounds(title->getX(), title->getY(), 1000, 15);
	this->title->setBorderSize(BorderSize<int>(0));

	flexBox = new FlexBox();
	flexBox->flexWrap = FlexBox::Wrap::wrap;
	flexBox->flexDirection = FlexBox::Direction::row;
	flexBox->justifyContent = FlexBox::JustifyContent::spaceBetween;

	addAndMakeVisible(title);
}

SliderPanel::~SliderPanel()
{
}

void SliderPanel::paint(Graphics& g)
{
	g.fillAll(background);
	g.setColour(borderColor);
	g.drawRect(borderPosintion.getX(), borderPosintion.getY(), getWidth() - 2 * borderPosintion.getX(), getHeight() - 2 * borderPosintion.getY(), (int)borderWidth);
}

void SliderPanel::resized()
{
	this->title->setBounds(borderPosintion.getX() + borderWidth + 3, borderPosintion.getY() + borderWidth + 3, title->getWidth(), title->getHeight());
	this->flexBox->performLayout(Rectangle<int>(Point<int>(this->title->getX(), this->title->getBottom() + 3), Point<int>(getWidth() - borderPosintion.getX(), getHeight() - borderPosintion.getY() - 3 - borderWidth)));
}

void SliderPanel::setBackgroundColor(juce::Colour color)
{
	background = color;
}

void SliderPanel::setBorderColour(juce::Colour color)
{
	borderColor = color;
}

void SliderPanel::setBorderWidth(float width)
{
	borderWidth = width;
}

void SliderPanel::setBorderPosition(Point<int> posintion)
{
	borderPosintion = posintion;
}

void SliderPanel::setTitle(Label* label)
{
	this->title = label;
}

void SliderPanel::setTitle(String text)
{
	this->title->setText(text, dontSendNotification);
}

void SliderPanel::setFlexBox(FlexBox* flexBox)
{
	this->flexBox = flexBox;
}

FlexBox* SliderPanel::getFlexBox()
{
	return flexBox;
}

void SliderPanel::addComponent(LabeledSlider* comp)
{
	flexBox->items.add(FlexItem(*comp).withMinWidth(50.0f).withMinHeight(50.0f).withFlex(2));
	addAndMakeVisible(comp);
	comp->addListener(this);
}

void SliderPanel::addListener(SliderListener* listener)
{
	listeners.push_back(listener);
}

void SliderPanel::sliderValueChanged(Slider* slider, String message)
{
	for (int i = 0; i < listeners.size(); i++)
		listeners[i]->sliderValueChanged(slider, title->getText() + L"~&#@" + message);
}

String SliderPanel::getTitle()
{
	return title->getText();
}
