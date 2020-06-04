#include "SliderPanel.h"
#include "LabeledSlider.h"

SliderPanel::SliderPanel()
{
	active.addListener(this);

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
{}

void SliderPanel::paint(Graphics& g)
{
	g.fillAll(background);
	g.setColour(borderColor);
	g.drawRect(borderPosintion.getX(), borderPosintion.getY(), getWidth() - 2 * borderPosintion.getX(), getHeight() - 2 * borderPosintion.getY(), (int)borderWidth);
}

void SliderPanel::resized()
{
	this->title->setBounds(borderPosintion.getX() + borderWidth + 3, borderPosintion.getY() + borderWidth + 3, title->getWidth(), title->getHeight());
	for (pair<Component*, ChildPosition> comp : cornersComponents)
	{
		if (auto button = dynamic_cast<TextButton*>(comp.first))
		{
			button->changeWidthToFitText();
		}
		float width = 0;
		for (pair<Component*, ChildPosition> comp2 : cornersComponents)
		{
			if (comp == comp2)
				break;
			if (comp.second == comp2.second)
			{
				switch (comp.second)
				{
				case ChildPosition::lowerLeftCorner:
					width = comp2.first->getWidth() + 3;
					break;
				case ChildPosition::lowerRightCorner:
					width = -comp2.first->getWidth() - 3;
					break;
				case ChildPosition::upperLeftCorner:
					width = comp2.first->getWidth() + 3;
					break;
				case ChildPosition::upperRightCorner:
					width = -comp2.first->getWidth() - 3;
					break;
				}
			}
		}
		float height = cornersHeightFactor >= 0 ? getHeight() * cornersHeightFactor : comp.first->getHeight();
		switch (comp.second)
		{
		case ChildPosition::lowerLeftCorner:
			comp.first->setBounds(borderPosintion.getX() + borderWidth + 3+width, getHeight()-borderPosintion.getY() - borderWidth - 3 - height, comp.first->getWidth(), height);
			break;
		case ChildPosition::lowerRightCorner:
			comp.first->setBounds(getWidth()-borderPosintion.getX() - borderWidth - 3-comp.first->getWidth() + width, getHeight() - borderPosintion.getY() - borderWidth - 3 - height, comp.first->getWidth(), height);
			break;
		case ChildPosition::upperLeftCorner:
			comp.first->setBounds(borderPosintion.getX() + borderWidth + 3 + width, borderPosintion.getY() + borderWidth + 3, comp.first->getWidth(), height);
			break;
		case ChildPosition::upperRightCorner:
			comp.first->setBounds(getWidth()- borderPosintion.getX() - borderWidth - 3-comp.first->getWidth() + width, borderPosintion.getY() +borderWidth + 3, comp.first->getWidth(), height);
			break;
		default:
			comp.first->setBounds(-comp.first->getWidth() - 1, -comp.first->getHeight() - 1, comp.first->getWidth(), comp.first->getHeight());
			break;
		}
	}
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

void SliderPanel::addComponent(Component* comp, ChildPosition position)
{
	if (position == ChildPosition::inFlexBox)
	{
		comp->addMouseListener(this, true);
		flexBox->items.add(FlexItem(*comp).withMinWidth(50.0f).withMinHeight(50.0f).withFlex(2));
	}
	else
	{
		cornersComponents.push_back(make_pair(comp, position));
	}
	addAndMakeVisible(comp);
}

String SliderPanel::getTitle()
{
	return title->getText();
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

float SliderPanel::getCornerHeightFactor()
{
	return cornersHeightFactor;
}

void SliderPanel::setCornerHeightFactor(float newFactor)
{
	cornersHeightFactor = newFactor;
}

void SliderPanel::setActive(Value active)
{
	this->active.referTo(active);
}

void SliderPanel::valueChanged(Value& value)
{
	if ((bool)this->active.getValue())
	{
		this->setBackgroundColor(Colours::darkslateblue);
		this->setBorderColour(Colours::grey);
	}
	else
	{
		this->setBackgroundColor(Colours::grey);
		this->setBorderColour(Colours::lightgrey);
	}
}
