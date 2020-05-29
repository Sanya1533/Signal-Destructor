#include "SliderPanel.h"
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
	this->repaint();
	resized();
}

void SliderPanel::setBorderColour(juce::Colour color)
{
	borderColor = color;
	this->repaint();
	resized();
}

void SliderPanel::setBorderWidth(float width)
{
	borderWidth = width;
	this->repaint();
	resized();
}

void SliderPanel::setBorderPosition(Point<int> posintion)
{
	borderPosintion = posintion;
	this->repaint();
	resized();
}

void SliderPanel::setTitle(Label* label)
{
	this->title = label;
	this->repaint();
	resized();
}

void SliderPanel::setTitle(String text)
{
	this->title->setText(text, dontSendNotification);
	this->repaint();
	resized();
}

void SliderPanel::setFlexBox(FlexBox* flexBox)
{
	this->flexBox = flexBox;
	this->repaint();
	resized();
}

FlexBox* SliderPanel::getFlexBox()
{
	return flexBox;
}

void SliderPanel::addComponent(LabeledSlider* comp)
{
	comp->addMouseListener(this, true);
	flexBox->items.add(FlexItem(*comp).withMinWidth(50.0f).withMinHeight(50.0f).withFlex(2));
	addAndMakeVisible(comp);
}

String SliderPanel::getTitle()
{
	return title->getText();
}

void SliderPanel::mouseDoubleClick(const MouseEvent& event)
{
	for (int i = 0; i < listeners.size(); i++)
		listeners[i]->mouseDoubleClick(this, event);
}

void SliderPanel::addListener(SliderPanel::MouseListener* listener)
{
	listeners.push_back(listener);
}

void SliderPanel::setActive(bool active)
{
	this->active.setValue(active);
}

Value SliderPanel::getActive()
{
	return active;
}

Component* SliderPanel::getChildByName(String title)
{
	Array<Component*> children = this->getChildren();
	for (auto child:children)
	{
		try
		{
			if (child->getName() == title)
			{
				return child;
			}
		}
		catch (const std::exception&)
		{
		}
	}
	return nullptr;
}

void SliderPanel::MouseListener::mouseDoubleClick(SliderPanel* panel, const MouseEvent& event)
{
}