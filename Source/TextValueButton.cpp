#include "TextValueButton.h"
#include <thread>
#include <chrono>

using namespace std;

TextValueButton::TextValueButton(String firstName, String* secondName, String firstText, String secondText)
{
	this->firstName = firstName;
	this->secondName = secondName;
	this->firstText = firstText;
	this->secondText = secondText;
	this->setActive(false);
	this->setClickingTogglesState(true);
	this->setBounds(0, 0, 100, 10);
}

TextValueButton::~TextValueButton()
{
}

void TextValueButton::setActive(bool active)
{
	this->active.setValue(active);
	if ((bool)this->active.getValue() || secondName == nullptr)
	{
		this->setButtonText(firstText);
	}
	else
	{
		this->setButtonText(secondText);
	}
}

Value TextValueButton::getActive()
{
	return active;
}

String TextValueButton::getFirstName()
{
	return firstName;
}

String TextValueButton::getSecondName()
{
	return *secondName;
}

bool TextValueButton::hasSecondName()
{
	return secondName != nullptr;
}

void TextValueButton::setFirstText(String newText)
{
	firstText = newText;
	setActive((bool)active.getValue());
}

void TextValueButton::setSecondText(String newText)
{
	secondText = newText;
	setActive((bool)active.getValue());
}

void TextValueButton::buttonClicked(Button* btn)
{
	setActive(!(bool)active.getValue());
	this->changeWidthToFitText();
	if (this->getParentComponent() != nullptr)
		this->getParentComponent()->resized();
}