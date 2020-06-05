#include "PluginEditor.h"
#include "SliderPanel.h"
#include "LabeledSlider.h"
#include "Languagesmanager.h"
#include "InterruptsCreator.h"
#include "NoiseCreator.h"
#include "SnapCreator.h"
#include "HumCreator.h"
#include "TextValueButton.h"
#include <JuceHeader.h>

//==============================================================================
SignalDestructorAudioProcessorEditor::SignalDestructorAudioProcessorEditor(SignalDestructorAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	Value value= Value(true);

	SliderPanel* interruptsSliderPanel = new SliderPanel();
	interruptsSliderPanel->setName(LanguagesManager::Properties::INTERRUPTS);

	interruptsSliderPanel->setBackgroundColor(Colours::darkslateblue);

	interruptsSliderPanel->setBorderColour(Colours::grey);

	interruptsSliderPanel->setBorderPosition(Point<int>(3, 3));

	interruptsSliderPanel->setBorderWidth(3);

	interruptsSliderPanel->setTitle(LanguagesManager::Properties::INTERRUPTS);

	interruptsSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::FREQUENCY));
	interruptsSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DURATION));
	interruptsSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::RANDOM_FACTOR, nullptr, 0, 100, 1));

	interruptsSliderPanel->addComponent(getParameteredButton(LanguagesManager::Properties::ACTIVE, LanguagesManager::Properties::MUTE, new String(LanguagesManager::Properties::UNMUTE), new String(LanguagesManager::Properties::TURN_OFF), new String(LanguagesManager::Properties::TURN_ON)), SliderPanel::ChildPosition::upperRightCorner);
	interruptsSliderPanel->addComponent(getParameteredButton(LanguagesManager::Properties::DEFAULT, new String(LanguagesManager::Properties::ZEROIZE)), SliderPanel::ChildPosition::upperRightCorner);
	interruptsSliderPanel->setCornerHeightFactor(0.13f);
	value = ((TextValueButton*)interruptsSliderPanel->getChildByName(LanguagesManager::Properties::ACTIVE))->getActive();

	p.addEffect(new InterruptsCreator(
		((LabeledSlider*)interruptsSliderPanel->getChildByName(LanguagesManager::Properties::FREQUENCY))->getSlider()->getValueObject(),
		((LabeledSlider*)interruptsSliderPanel->getChildByName(LanguagesManager::Properties::DURATION))->getSlider()->getValueObject(),
		((LabeledSlider*)interruptsSliderPanel->getChildByName(LanguagesManager::Properties::RANDOM_FACTOR))->getSlider()->getValueObject(),
		value
	));
	interruptsSliderPanel->setActive(value);

	SliderPanel* noiseSliderPanel = new SliderPanel();
	noiseSliderPanel->setName(LanguagesManager::Properties::NOISE);

	noiseSliderPanel->setBackgroundColor(Colours::darkslateblue);

	noiseSliderPanel->setBorderColour(Colours::grey);

	noiseSliderPanel->setBorderPosition(Point<int>(3, 3));

	noiseSliderPanel->setBorderWidth(3);

	noiseSliderPanel->setTitle(LanguagesManager::Properties::NOISE);

	noiseSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::FREQUENCY));
	noiseSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DURATION));
	noiseSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::VOLUME, nullptr, 0, 100, 0.01));
	noiseSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::RANDOM_FACTOR, nullptr, 0, 100, 1));

	noiseSliderPanel->addComponent(getParameteredButton(LanguagesManager::Properties::ACTIVE, LanguagesManager::Properties::MUTE, new String(LanguagesManager::Properties::UNMUTE), new String(LanguagesManager::Properties::TURN_OFF), new String(LanguagesManager::Properties::TURN_ON)), SliderPanel::ChildPosition::upperRightCorner);
	noiseSliderPanel->addComponent(getParameteredButton(LanguagesManager::Properties::DEFAULT, new String(LanguagesManager::Properties::ZEROIZE)), SliderPanel::ChildPosition::upperRightCorner);
	noiseSliderPanel->setCornerHeightFactor(0.13f);
	value=((TextValueButton*)noiseSliderPanel->getChildByName(LanguagesManager::Properties::ACTIVE))->getActive();

	
	p.addEffect(new NoiseCreator(
		((LabeledSlider*)noiseSliderPanel->getChildByName(LanguagesManager::Properties::FREQUENCY))->getSlider()->getValueObject(),
		((LabeledSlider*)noiseSliderPanel->getChildByName(LanguagesManager::Properties::DURATION))->getSlider()->getValueObject(),
		((LabeledSlider*)noiseSliderPanel->getChildByName(LanguagesManager::Properties::VOLUME))->getSlider()->getValueObject(),
		((LabeledSlider*)noiseSliderPanel->getChildByName(LanguagesManager::Properties::RANDOM_FACTOR))->getSlider()->getValueObject(),
		value
	));
	noiseSliderPanel->setActive(value);

	SliderPanel* snapSliderPanel = new SliderPanel();
	snapSliderPanel->setName(LanguagesManager::Properties::CRACKLING);

	snapSliderPanel->setBackgroundColor(Colours::darkslateblue);

	snapSliderPanel->setBorderColour(Colours::grey);

	snapSliderPanel->setBorderPosition(Point<int>(3, 3));

	snapSliderPanel->setBorderWidth(3);

	snapSliderPanel->setTitle(LanguagesManager::Properties::CRACKLING);

	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::FREQUENCY));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DURATION));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::VOLUME, nullptr, 0, 100, 0.01));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::RANDOM_FACTOR, nullptr, 0, 100, 1));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DENSITY, nullptr, 0, 120, 0.1));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::CLIPPING_FACTOR, nullptr, 0, 20, 0.1));

	snapSliderPanel->addComponent(getParameteredButton(LanguagesManager::Properties::ACTIVE, LanguagesManager::Properties::MUTE, new String(LanguagesManager::Properties::UNMUTE), new String(LanguagesManager::Properties::TURN_OFF), new String(LanguagesManager::Properties::TURN_ON)), SliderPanel::ChildPosition::upperRightCorner);
	snapSliderPanel->addComponent(getParameteredButton(LanguagesManager::Properties::DEFAULT, new String(LanguagesManager::Properties::ZEROIZE)), SliderPanel::ChildPosition::upperRightCorner);
	snapSliderPanel->setCornerHeightFactor(0.13f);
	value = ((TextValueButton*)snapSliderPanel->getChildByName(LanguagesManager::Properties::ACTIVE))->getActive();

	p.addEffect(new SnapCreator(
		((LabeledSlider*)snapSliderPanel->getChildByName(LanguagesManager::Properties::FREQUENCY))->getSlider()->getValueObject(),
		((LabeledSlider*)snapSliderPanel->getChildByName(LanguagesManager::Properties::DURATION))->getSlider()->getValueObject(),
		((LabeledSlider*)snapSliderPanel->getChildByName(LanguagesManager::Properties::VOLUME))->getSlider()->getValueObject(),
		((LabeledSlider*)snapSliderPanel->getChildByName(LanguagesManager::Properties::RANDOM_FACTOR))->getSlider()->getValueObject(),
		((LabeledSlider*)snapSliderPanel->getChildByName(LanguagesManager::Properties::DENSITY))->getSlider()->getValueObject(),
		((LabeledSlider*)snapSliderPanel->getChildByName(LanguagesManager::Properties::CLIPPING_FACTOR))->getSlider()->getValueObject(),
		value
	));
	snapSliderPanel->setActive(value);

	SliderPanel* humSliderPanel = new SliderPanel();
	humSliderPanel->setName(LanguagesManager::Properties::BUZZING);

	humSliderPanel->setBackgroundColor(Colours::darkslateblue);

	humSliderPanel->setBorderColour(Colours::grey);

	humSliderPanel->setBorderPosition(Point<int>(3, 3));

	humSliderPanel->setBorderWidth(3);

	humSliderPanel->setTitle(LanguagesManager::Properties::BUZZING);

	humSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::FREQUENCY));
	humSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DURATION));
	humSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::VOLUME, nullptr, 0, 100, 0.01));
	humSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::RANDOM_FACTOR, nullptr, 0, 100, 1));

	humSliderPanel->addComponent(getParameteredButton(LanguagesManager::Properties::ACTIVE, LanguagesManager::Properties::MUTE, new String(LanguagesManager::Properties::UNMUTE), new String(LanguagesManager::Properties::TURN_OFF), new String(LanguagesManager::Properties::TURN_ON)), SliderPanel::ChildPosition::upperRightCorner);
	humSliderPanel->addComponent(getParameteredButton(LanguagesManager::Properties::DEFAULT, new String(LanguagesManager::Properties::ZEROIZE)), SliderPanel::ChildPosition::upperRightCorner);
	humSliderPanel->setCornerHeightFactor(0.13f);
	value = ((TextValueButton*)humSliderPanel->getChildByName(LanguagesManager::Properties::ACTIVE))->getActive();

	p.addEffect(new HumCreator(
		((LabeledSlider*)humSliderPanel->getChildByName(LanguagesManager::Properties::FREQUENCY))->getSlider()->getValueObject(),
		((LabeledSlider*)humSliderPanel->getChildByName(LanguagesManager::Properties::DURATION))->getSlider()->getValueObject(),
		((LabeledSlider*)humSliderPanel->getChildByName(LanguagesManager::Properties::VOLUME))->getSlider()->getValueObject(),
		((LabeledSlider*)humSliderPanel->getChildByName(LanguagesManager::Properties::RANDOM_FACTOR))->getSlider()->getValueObject(),
		value
	));
	humSliderPanel->setActive(value);

	panels.push_back(interruptsSliderPanel);
	panels.push_back(noiseSliderPanel);
	panels.push_back(snapSliderPanel);
	panels.push_back(humSliderPanel);

	setListenersToTextEditors();

	for (const SliderPanel* panel : panels)
	{
		for (Component* comp : panel->getChildren())
		{
			if (auto slider = dynamic_cast<LabeledSlider*>(comp))
			{
				const String name = panel->getName()+"->"+comp->getName();
				processor.addParameter(name, slider->getSlider());
			}
			else
			{
				if (TextValueButton* button = dynamic_cast<TextValueButton*>(comp))
				{
					const String name = panel->getName() + "->" + button->getName();
					processor.addParameter(name, button);
				}
			}
		}
	}
	languages = new ComboBox();
	vector<wstring> localLangs = LanguagesManager::getProperty(LanguagesManager::Properties::LOCAL_LANG_FIELD, nullptr, true);
	int id = 1;
	if (localLangs.size() > 0)
	{
		for (wstring lang : localLangs)
		{
			languages->addItem(String(lang.c_str()), id++);
		}
	}
	else
	{
		languages->addItem("English", id++);
	}
	languages->setJustificationType(Justification::centred);
	wstring* str = LanguagesManager::getCurrentLanguage();
	for (int i = 0; i < languages->getNumItems(); i++)
	{
		if (str==nullptr||*str == languages->getItemText(i).toWideCharPointer())
		{
			languages->setSelectedItemIndex(i, dontSendNotification);
			comboBoxChanged(languages);
			break;
		}
	}
	languages->addListener(this);

	addAndMakeVisible(interruptsSliderPanel);
	addAndMakeVisible(noiseSliderPanel);
	addAndMakeVisible(snapSliderPanel);
	addAndMakeVisible(humSliderPanel);
	addAndMakeVisible(languages);


	setSize(900, 600);	
}

SignalDestructorAudioProcessorEditor::~SignalDestructorAudioProcessorEditor()
{
}

//==============================================================================
void SignalDestructorAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void SignalDestructorAudioProcessorEditor::resized()
{
	int heihgt = getHeight() * 24 / 25;
	languages->setBounds(0, 0, getWidth(), getHeight() / 25);
	for (int i = 0; i < panels.size(); i++)
	{
		panels[i]->setBounds(0, getHeight() / 25 + heihgt / panels.size() * i, getWidth(), heihgt / panels.size());
	}
}

void SignalDestructorAudioProcessorEditor::comboBoxChanged(ComboBox* changedComboBox)
{
try{
	if (changedComboBox == languages)
	{
		String lang;
		if ((languages->getText()) != "")
		{
			wstring localLang = languages->getText().toWideCharPointer();
			LanguagesManager::setCurrentLanguage(localLang);
			vector<wstring> vec;
			for (SliderPanel* panel : panels)
			{
				vec = LanguagesManager::getProperty(panel->getName().toStdString(), &localLang);
				if (vec.size() > 0)
				{
					panel->setTitle(vec[0].c_str());
					for (Component* child : panel->getChildren())
					{
						if (auto particularChild = dynamic_cast<LabeledSlider*>(child))
						{
							vec = LanguagesManager::getProperty(particularChild->getName().toStdString(), &localLang);
							if (vec.size() > 0)
							{
								particularChild->setText(vec[0].c_str());
							}
						}
						else
						{
							if (auto textButton = dynamic_cast<TextValueButton*>(child))
							{
								vec = LanguagesManager::getProperty(textButton->getFirstName().toStdString(), &localLang);
								if (vec.size() > 0)
								{
									textButton->setFirstText(vec[0].c_str());
								}
								vec = LanguagesManager::getProperty(textButton->getSecondName().toStdString(), &localLang);
								if (vec.size() > 0)
								{
									textButton->setSecondText(vec[0].c_str());
								}
							}
							else
							{
								if (auto particularChild2 = dynamic_cast<TextButton*>(child))
								{
									vec = LanguagesManager::getProperty(particularChild2->getName().toStdString(), &localLang);
									if (vec.size() > 0)
									{
										particularChild2->setButtonText(vec[0].c_str());
									}
								}
							}
						}
					}
				}
				panel->resized();
			}
		}
	}
}
catch(std::exception& ex)
{
}
}

LabeledSlider* SignalDestructorAudioProcessorEditor::getParametredSlider(String text, String* name, double minValue, double maxValue, double interval, LabeledSlider::LabelPosition labelPosition, Slider::TextEntryBoxPosition boxPosition, Slider::SliderStyle style, double labelPercentage)
{
	LabeledSlider* labeledSlider = new LabeledSlider(new Slider(style, boxPosition), new Label(text, text), labelPosition, labelPercentage);
	labeledSlider->setRange(&minValue, &maxValue, &interval);

	labeledSlider->setName(name != nullptr ? *name : text);
	return labeledSlider;
}

TextValueButton* SignalDestructorAudioProcessorEditor::getParameteredButton(String text, String firstName, String* secondName, String* firstText, String* secondText)
{
	TextValueButton* button = new TextValueButton(firstName, secondName, firstText != nullptr ? *firstText : firstName,
		secondText != nullptr ? *secondText : secondName == nullptr?"": *secondName);
	button->addListener(button);
	button->triggerClick();
	button->setName(text);
	return button;
}

TextButton* SignalDestructorAudioProcessorEditor::getParameteredButton(String name, String* text)
{
	TextButton* button = new TextButton(name);
	button->setBounds(0, 0, 100, 20);
	button->setButtonText(text!=nullptr?*text:name);
	button->addListener(this);
	button->changeWidthToFitText();
	return button;
}

void SignalDestructorAudioProcessorEditor::setListenersToTextEditors()
{
	for (auto panel : panels)
	{
		for (auto child : panel->getChildren())
		{
			if (auto sliderPanel = dynamic_cast<LabeledSlider*>(child))
			{
				for (auto sliderChild : sliderPanel->getSlider()->getChildren())
				{
					if (auto label = dynamic_cast<Label*>(sliderChild))
					{
						label->onEditorShow = [this, label]()
						{
							if (label->getCurrentTextEditor() != nullptr)
							{
								label->getCurrentTextEditor()->addKeyListener(this);
							}
						};
					}
				}
			}
		}
	}
}

void SignalDestructorAudioProcessorEditor::buttonClicked(Button* button)
{
	if (auto textButton = dynamic_cast<TextButton*>(button))
	{
		if (auto panel = dynamic_cast<SliderPanel*>(button->getParentComponent()))
		{
			for (auto child : panel->getChildren())
			{
				if (auto slider = dynamic_cast<LabeledSlider*>(child))
				{
					slider->getSlider()->setValue(0.0f, sendNotificationAsync);
				}
			}
		}
	}
}

bool SignalDestructorAudioProcessorEditor::keyPressed(const KeyPress& key, Component* originatingComponent)
{
	if (auto editor=dynamic_cast<TextEditor*>(originatingComponent))
	{ 
		if (key.getTextDescription()=="ctrl + V")
		{
			if (OpenClipboard(0))
			{
				HANDLE hData = GetClipboardData(CF_TEXT);
				String chBuffer = (char*)GlobalLock(hData);
				GlobalUnlock(hData);
				CloseClipboard();
				String text = editor->getText().replaceSection(editor->getHighlightedRegion().getStart(), editor->getHighlightedRegion().getEnd(), chBuffer);
				text = modifyText(text.toStdString());
				if (text.length() > 0)
				{
					if (editor->getHighlightedText().length() > 0)
						editor->deleteBackwards(false);
					int index = editor->getCaretPosition();
					editor->setText(text);
					editor->moveCaretRight(false, false);
				}
			}
			return true;
		}
		if (key.getModifiers().isAnyModifierKeyDown()||key.isKeyCode(KeyPress::insertKey))
			return false;
		if (key.isKeyCode(13))//Enter
			return false;
		if (key.isKeyCode(KeyPress::leftKey) || key.isKeyCode(KeyPress::rightKey) || key.isKeyCode(KeyPress::upKey) || key.isKeyCode(KeyPress::downKey))
			return false;
		if (key.isKeyCode(KeyPress::deleteKey) || key.isKeyCode(KeyPress::backspaceKey))
			return false;
		if (key.getTextCharacter() >= '0' && key.getTextCharacter() <= '9')
		{
			return false;
		} 
		if (key.getTextCharacter() == '.' || key.getTextCharacter() == ',')
		{
			String text = editor->getText().replaceSection(editor->getHighlightedRegion().getStart(), editor->getHighlightedRegion().getEnd(),".");
			text = modifyText(text.toStdString());
			if (text.length()>0)
			{
				if (editor->getHighlightedText().length() > 0)
					editor->deleteBackwards(false);
				int index = editor->getCaretPosition();
				editor->setText(text);
				editor->moveCaretRight(false, false);
			}
			return true;
		}
		return true;
	}
	return false;
}

String SignalDestructorAudioProcessorEditor::modifyText(string text)
{
	string newText;
	bool separator = false;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] >= '0' && text[i] <= '9' || text[i] == '.' || text[i] == ',')
		{
			if (text[i] == '.' || text[i] == ',')
			{
				if (!separator &&newText.length() > 0)
				{
					newText += '.';
					separator = true;
				}
			}
			else
			{
				if (separator|| newText.length() == 0|| newText[0] != '0')
				{
					newText += text[i];
				}
				else
				{
					if (text[i] != '0')
					{
						newText = text[i];
					}
				}
			}
		}
	}
	return newText;
}