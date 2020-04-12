#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
YearprojectAudioProcessorEditor::YearprojectAudioProcessorEditor (YearprojectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	interruptsSliderPanel = new SliderPanel();

	interruptsSliderPanel->setBackgroundColor(Colours::darkblue);

	interruptsSliderPanel->setBorderColour(Colours::grey);

	interruptsSliderPanel->setBorderPosition(Point<int>(3, 3));

	interruptsSliderPanel->setBorderWidth(3);

	interruptsSliderPanel->setTitle(L"Прерывания");


	interruptsSliderPanel->addComponent(getParametredSlider(L"Частота"));
	interruptsSliderPanel->addComponent(getParametredSlider(L"Длительность", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	interruptsSliderPanel->addComponent(getParametredSlider(L"Густота прерываний", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));
	interruptsSliderPanel->addListener(this);


	noiseSliderPanel = new SliderPanel();

	noiseSliderPanel->setBackgroundColor(Colours::darkblue);

	noiseSliderPanel->setBorderColour(Colours::grey);

	noiseSliderPanel->setBorderPosition(Point<int>(3, 3));

	noiseSliderPanel->setBorderWidth(3);

	noiseSliderPanel->setTitle(L"Шум");

	noiseSliderPanel->addComponent(getParametredSlider(L"Частота", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	noiseSliderPanel->addComponent(getParametredSlider(L"Длительность", LabeledSlider::LabelAbove, Slider::NoTextBox));
	noiseSliderPanel->addComponent(getParametredSlider(L"Громкость", LabeledSlider::LabelBelow, Slider::NoTextBox, 0, 100, 0.01));

	noiseSliderPanel->addListener(this);


	snapSliderPanel = new SliderPanel();

	snapSliderPanel->setBackgroundColor(Colours::darkblue);

	snapSliderPanel->setBorderColour(Colours::grey);

	snapSliderPanel->setBorderPosition(Point<int>(3, 3));

	snapSliderPanel->setBorderWidth(3);

	snapSliderPanel->setTitle(L"Треск");

	snapSliderPanel->addComponent(getParametredSlider(L"Частота", LabeledSlider::LabelBelow, Slider::TextBoxAbove));
	snapSliderPanel->addComponent(getParametredSlider(L"Длительность"));
	snapSliderPanel->addComponent(getParametredSlider(L"Громкость", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));

	snapSliderPanel->addListener(this);


	humSliderPanel = new SliderPanel();

	humSliderPanel->setBackgroundColor(Colours::darkblue);

	humSliderPanel->setBorderColour(Colours::grey);

	humSliderPanel->setBorderPosition(Point<int>(3, 3));

	humSliderPanel->setBorderWidth(3);

	humSliderPanel->setTitle(L"Гудение");

	humSliderPanel->addComponent(getParametredSlider(L"Частота", LabeledSlider::LabelAbove, Slider::NoTextBox));
	humSliderPanel->addComponent(getParametredSlider(L"Длительность", LabeledSlider::LabelAbove, Slider::TextBoxBelow));
	humSliderPanel->addComponent(getParametredSlider(L"Громкость", LabeledSlider::LabelAbove, Slider::TextBoxBelow, 0, 100, 0.01));

	humSliderPanel->addListener(this);


	addAndMakeVisible(interruptsSliderPanel);
	addAndMakeVisible(noiseSliderPanel);
	addAndMakeVisible(snapSliderPanel);
	addAndMakeVisible(humSliderPanel);

	setSize(1000, 600);
}

YearprojectAudioProcessorEditor::~YearprojectAudioProcessorEditor()
{
}

//==============================================================================
void YearprojectAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void YearprojectAudioProcessorEditor::resized()
{
	interruptsSliderPanel->setBounds(0, 0, getWidth(), getHeight() / 4);
	noiseSliderPanel->setBounds(0, getHeight() / 4, getWidth(), getHeight() / 4);
	snapSliderPanel->setBounds(0, getHeight() / 2, getWidth(), getHeight() / 4);
	humSliderPanel->setBounds(0, getHeight() * 3 / 4, getWidth(), getHeight() / 4);
}

void YearprojectAudioProcessorEditor::sliderValueChanged(Slider* slider, String message)
{
	String firstMessage = message.substring(0, message.indexOf("~&#@"));
	String secondMessage = message.substring(message.indexOf("~&#@") + 4);

	if (firstMessage == interruptsSliderPanel->getTitle())
	{
		if (secondMessage == interruptsFrequencySlider->getLabel()->getText())
		{
		}
		else
		{
			if (secondMessage == interruptsDurationSlider->getLabel()->getText())
			{
			}
			else
			{
				if (secondMessage == countOfInterruptsSlider->getLabel()->getText())
				{
				}
			}
		}
	}
	else
	{
		if (firstMessage == noiseSliderPanel->getTitle())
		{
			if (secondMessage == noiseFrequencySlider->getLabel()->getText())
			{
			}
			else
			{
				if (secondMessage == noiseDurationSlider->getLabel()->getText())
				{
				}
				else
				{
					if (secondMessage == noiseVolumeSlider->getLabel()->getText())
					{
					}
				}
			}
		}
		else
		{
			if (firstMessage == snapSliderPanel->getTitle())
			{
				if (secondMessage == snapFrequencySlider->getLabel()->getText())
				{
				}
				else
				{
					if (secondMessage == snapDurationSlider->getLabel()->getText())
					{
					}
					else
					{
						if (secondMessage == snapVolumeSlider->getLabel()->getText())
						{
						}
					}
				}
			}
			else
			{
				if (firstMessage == humSliderPanel->getTitle())
				{
					if (secondMessage == humFrequencySlider->getLabel()->getText())
					{
					}
					else
					{
						if (secondMessage == humDurationSlider->getLabel()->getText())
						{
						}
						else
						{
							if (secondMessage == humVolumeSlider->getLabel()->getText())
							{
							}
						}
					}
				}
			}
		}
	}
}

LabeledSlider* YearprojectAudioProcessorEditor::getParametredSlider(String text, LabeledSlider::LabelPosition labelPosition, Slider::TextEntryBoxPosition boxPosition, double minValue, double maxValue, double interval, Slider::SliderStyle style, double labelPercentage)
{
	LabeledSlider* labeledSlider = new LabeledSlider(new Slider(style, boxPosition), new Label("", text), labelPosition, labelPercentage);
	labeledSlider->setRange(minValue, maxValue, interval);
	return labeledSlider;
}
