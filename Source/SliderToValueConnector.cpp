//#include "SliderToValueConnector.h"
//
//
//template<typename T>
//SliderToValueConnector<T>::SliderToValueConnector(T value)
//{
//    (*this->value) = value;
//}
//
//template<typename T>
//double SliderToValueConnector<T>::getValue()
//{
//	return *value;
//}
//
//template<typename T>
//void SliderToValueConnector<T>::setValue(T newValue)
//{
//    (*this->value) = newValue;
//}
//
//template<typename T>
//void SliderToValueConnector<T>::setVariable(T  *varToChange)
//{
//    (*varToChange) = (*this->value);
//    this->value = varToChange;
//}
//
//template<typename T>
//void SliderToValueConnector<T>::setSourceSlider(Slider* slider)
//{
//    slider->addListener(this);
//}
//
//template<typename T>
//void SliderToValueConnector<T>::sliderValueChanged(Slider* slider)
//{
//    (*this->value)= slider->getValue();
//}