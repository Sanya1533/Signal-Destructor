#pragma once
#include <JuceHeader.h>

class TextValueButton :public TextButton,public TextButton::Listener
{
public:
	TextValueButton(String firstName, String* secondName, String firstText, String secondText);
	~TextValueButton();

	void TextValueButton::setActive(bool active);

	Value TextValueButton::getActive();

	String getFirstName();
	String getSecondName();
	bool hasSecondName();

	void setFirstText(String newText);
	void setSecondText(String newText);
	void buttonClicked(Button*) override;

private:
	String firstName;
	String* secondName;

	String firstText;
	String secondText;

	Value active = Value(true);

	bool deleteListener=false;
};