#include "PluginEditor.h"
#include "SliderPanel.h"
#include "LabeledSlider.h"
#include "LanguagesManager.h"
#include "InterruptsCreator.h"
#include "NoiseCreator.h"
#include "SnapCreator.h"
#include "HumCreator.h"
#include <JuceHeader.h>
#include <vector>
#include <fstream>
#include <map>

//==============================================================================
YearprojectAudioProcessorEditor::YearprojectAudioProcessorEditor(YearprojectAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
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


	p.addEffect(new InterruptsCreator(
		interruptsSliderPanel->getChildWithTitle(LanguagesManager::Properties::FREQUENCY)->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(LanguagesManager::Properties::DURATION)->getSlider()->getValueObject(),
		interruptsSliderPanel->getChildWithTitle(LanguagesManager::Properties::RANDOM_FACTOR)->getSlider()->getValueObject(),
		interruptsSliderPanel->getActive()
	));

	//sld = new AudioProcessorValueTreeState::SliderAttachment(processor.parameters, "1", *interruptsSliderPanel->getChildWithTitle(LanguagesManager::Properties::FREQUENCY)->getSlider());

	interruptsSliderPanel->addListener(this);


	SliderPanel*  noiseSliderPanel = new SliderPanel();
	noiseSliderPanel->setName(LanguagesManager::Properties::NOISE);

	noiseSliderPanel->setBackgroundColor(Colours::darkslateblue);

	noiseSliderPanel->setBorderColour(Colours::grey);

	noiseSliderPanel->setBorderPosition(Point<int>(3, 3));

	noiseSliderPanel->setBorderWidth(3);

	noiseSliderPanel->setTitle(LanguagesManager::Properties::NOISE);

	noiseSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::FREQUENCY));
	noiseSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DURATION));
	noiseSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::VOLUME, nullptr,0, 100, 0.01));
	noiseSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::RANDOM_FACTOR,nullptr, 0, 100, 1));

	p.addEffect(new NoiseCreator(
		noiseSliderPanel->getChildWithTitle(LanguagesManager::Properties::FREQUENCY)->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(LanguagesManager::Properties::DURATION)->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(LanguagesManager::Properties::VOLUME)->getSlider()->getValueObject(),
		noiseSliderPanel->getChildWithTitle(LanguagesManager::Properties::RANDOM_FACTOR)->getSlider()->getValueObject(),
		noiseSliderPanel->getActive()
	));

	noiseSliderPanel->addListener(this);


	SliderPanel* snapSliderPanel = new SliderPanel();
	snapSliderPanel->setName(LanguagesManager::Properties::CRACKLING);

	snapSliderPanel->setBackgroundColor(Colours::darkslateblue);

	snapSliderPanel->setBorderColour(Colours::grey);

	snapSliderPanel->setBorderPosition(Point<int>(3, 3));

	snapSliderPanel->setBorderWidth(3);

	snapSliderPanel->setTitle(LanguagesManager::Properties::CRACKLING);

	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::FREQUENCY));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DURATION));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::VOLUME,nullptr, 0, 100, 0.01));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::RANDOM_FACTOR,nullptr, 0, 100, 1));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DENSITY, nullptr,0, 44099, 1));
	snapSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::CLIPPING_FACTOR,nullptr, 0, 300, 0.1));

	p.addEffect(new SnapCreator(
		snapSliderPanel->getChildWithTitle(LanguagesManager::Properties::FREQUENCY)->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(LanguagesManager::Properties::DURATION)->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(LanguagesManager::Properties::VOLUME)->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(LanguagesManager::Properties::RANDOM_FACTOR)->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(LanguagesManager::Properties::DENSITY)->getSlider()->getValueObject(),
		snapSliderPanel->getChildWithTitle(LanguagesManager::Properties::CLIPPING_FACTOR)->getSlider()->getValueObject(),
		snapSliderPanel->getActive()
	));

	snapSliderPanel->addListener(this);


	SliderPanel* humSliderPanel = new SliderPanel();
	humSliderPanel->setName(LanguagesManager::Properties::BUZZING);

	humSliderPanel->setBackgroundColor(Colours::darkslateblue);

	humSliderPanel->setBorderColour(Colours::grey);

	humSliderPanel->setBorderPosition(Point<int>(3, 3));

	humSliderPanel->setBorderWidth(3);

	humSliderPanel->setTitle(LanguagesManager::Properties::BUZZING);

	humSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::FREQUENCY));
	humSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::DURATION));
	humSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::VOLUME,nullptr, 0, 100, 0.01));
	humSliderPanel->addComponent(getParametredSlider(LanguagesManager::Properties::RANDOM_FACTOR,nullptr, 0, 20, 0.01));

	p.addEffect(new HumCreator(
		humSliderPanel->getChildWithTitle(LanguagesManager::Properties::FREQUENCY)->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(LanguagesManager::Properties::DURATION)->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(LanguagesManager::Properties::VOLUME)->getSlider()->getValueObject(),
		humSliderPanel->getChildWithTitle(LanguagesManager::Properties::RANDOM_FACTOR)->getSlider()->getValueObject(),
		humSliderPanel->getActive()
	));

	humSliderPanel->addListener(this);
		languages = new ComboBox();
		vector<wstring> localLangs = LanguagesManager::getProperty(LanguagesManager::Properties::LOCAL_LANG_FIELD, nullptr, true);
		vector<wstring> langs = LanguagesManager::getProperty(LanguagesManager::Properties::LANGFIELD, nullptr, true);
		int id = 1;
		if (langs.size() > 0)
		{
			for (int i = 0; i < langs.size(); i++)
			{
				//langMap[localLangs[i]]= langs[i];
				languages->addItem(String(localLangs[i].c_str()), id++);
				languages->addItem(String(langs[i].c_str()), id++);
			}
			//for (wstring lang : localLangs)
			//{
			//	languages->addItem(String(lang.c_str()), id++);
			//}
		}
		else
		{
			langMap[L"English"]= L"English";
			languages->addItem("English", id++);
		}
		languages->setJustificationType(Justification::centred);
	    wstring* str = LanguagesManager::getCurrentLanguage();
		if (str == nullptr)
		{
			str = new wstring(L"sss");
		}
		languages->addItem(str->c_str(), 8963);
		//for (int i = 0; i < languages->getNumItems(); i++)
		//{
		//	languages->changeItemText(i, String(langMap[languages->getItemText(i).toWideCharPointer()].c_str()));
		//	//if (*str == langMap[languages->getItemText(i).toWideCharPointer()])
		//	//{
		//	//	languages->setSelectedItemIndex(i, dontSendNotification);
		//	//	comboBoxChanged(languages);
		//	//	break;
		//	//}
		//}
		languages->addListener(this);
		addAndMakeVisible(interruptsSliderPanel);
		addAndMakeVisible(noiseSliderPanel);
		addAndMakeVisible(snapSliderPanel);
		addAndMakeVisible(humSliderPanel);
		addAndMakeVisible(languages);
		panels.push_back(interruptsSliderPanel);
		panels.push_back(noiseSliderPanel);
		panels.push_back(snapSliderPanel);
		panels.push_back(humSliderPanel);
	
	setSize(900, 700);
	
}

YearprojectAudioProcessorEditor::~YearprojectAudioProcessorEditor()
{
}

//==============================================================================
void YearprojectAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void YearprojectAudioProcessorEditor::resized()
{
	int heihgt = getHeight() * 24 / 25;
	languages->setBounds(0, 0, getWidth(), getHeight() / 25);
	for (int i = 0; i < panels.size(); i++)
	{
		panels[i]->setBounds(0, getHeight() / 25 + heihgt / panels.size() * i, getWidth(), heihgt / panels.size());
	}
}

void YearprojectAudioProcessorEditor::mouseDoubleClick(SliderPanel* panel, const MouseEvent& event)
{
	if ((bool)panel->getActive().getValue())
	{
		panel->setBackgroundColor(Colours::grey);
		panel->setBorderColour(Colours::lightgrey);
	}
	else
	{
		panel->setBackgroundColor(Colours::darkslateblue);
		panel->setBorderColour(Colours::grey);
	}
	panel->setActive(!(bool)panel->getActive().getValue());
}

void YearprojectAudioProcessorEditor::comboBoxChanged(ComboBox* changedComboBox)
{
	//if (changedComboBox == languages)
	//{
	//	String lang;
	//	if ((languages->getText()) != "")
	//	{
	//		wstring localLang = languages->getText().toWideCharPointer();
	//		LanguagesManager::setCurrentLanguage(localLang);
	//		vector<wstring> vec;
	//		for (SliderPanel* panel : panels)
	//		{
	//			vec = LanguagesManager::getProperty(panel->getName().toStdString(), &localLang);
	//			if (vec.size() > 0)
	//			{
	//				panel->setTitle(vec[0].c_str());
	//			}
	//		}
	//	}
	//}
}

LabeledSlider* YearprojectAudioProcessorEditor::getParametredSlider(String text,String* name, double minValue, double maxValue, double interval, LabeledSlider::LabelPosition labelPosition, Slider::TextEntryBoxPosition boxPosition, Slider::SliderStyle style, double labelPercentage)
{
	LabeledSlider* labeledSlider = new LabeledSlider(new Slider(style, boxPosition), new Label(text, text), labelPosition, labelPercentage);
	labeledSlider->setRange(minValue, maxValue, interval);
	labeledSlider->setName(name!=nullptr?*name:text);
	return labeledSlider;
}