#pragma once

#include "ofMain.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiRangeSlider.h"
#include "Gui2dPad.h"
#include "GuiWidgetBase.h"
#include "GuiColor.h"
#include "GuiMenu.h"


class GuiWidget : public GuiWidgetBase
{
public:
    GuiWidget();
    GuiWidget(string name);
    virtual ~GuiWidget();
    
    void addButton(Parameter<bool> *parameter);
    void addButton(string name, bool *value);
    template<typename L, typename M>
    void addButton(Parameter<bool> *parameter, L *listener, M method);
    template<typename L, typename M>
    void addButton(string name, bool *value, L *listener, M method);
    template<typename L, typename M>
    void addButton(string name, L *listener, M method);
    
    void addToggle(Parameter<bool> *parameter);
    void addToggle(string name, bool *value);
    template<typename L, typename M>
    void addToggle(Parameter<bool> *parameter, L *listener, M method);
    template<typename L, typename M>
    void addToggle(string name, bool *value, L *listener, M method);
    template<typename L, typename M>
    void addToggle(string name, L *listener, M method);
    
    template<typename T>
    void addSlider(Parameter<T> *parameter);
    template<typename T>
    void addSlider(string name, T *value, T min, T max);
    template<typename T, typename L, typename M>
    void addSlider(Parameter<T> *parameter, L *listener, M method);
    template<typename T, typename L, typename M>
    void addSlider(string name, T *value, T min, T max, L *listener, M method);

    template<typename T>
    void addRangeSlider(string name, Parameter<T> *parameterLow, Parameter<T> *parameterHigh);
    template<typename T>
    void addRangeSlider(string name, T *valueLow, T *valueHigh, T min, T max);
    template<typename T, typename L, typename M>
    void addRangeSlider(string name, Parameter<T> *parameterLow, Parameter<T> *parameterHigh, L *listener, M method);
    template<typename T, typename L, typename M>
    void addRangeSlider(string name, T *valueLow, T *valueHigh, T min, T max, L *listener, M method);
    
    void add2dPad(Parameter<ofPoint> *parameter);
    void add2dPad(string name, ofPoint *value, ofPoint min, ofPoint max);
    template<typename L, typename M>
    void add2dPad(Parameter<ofPoint> *parameter, L *listener, M method);
    template<typename L, typename M>
    void add2dPad(string name, ofPoint *value, ofPoint min, ofPoint max, L *listener, M method);
    
    void addColor(Parameter<ofFloatColor> *parameter);
    void addColor(string name, ofFloatColor * parameter, ofFloatColor min, ofFloatColor max);
    void addColor(string name, ofFloatColor * parameter);
    template<typename L, typename M>
    void addColor(Parameter<ofFloatColor> *parameter, L *listener, M method);
    template<typename L, typename M>
    void addColor(string name, ofFloatColor * parameter, ofFloatColor min, ofFloatColor max, L *listener, M method);
    template<typename L, typename M>
    void addColor(string name, ofFloatColor * parameter, L *listener, M method);
    
    GuiMenu * addMenu(string name, vector<string> choices, bool multipleChoice=false, bool autoClose=false);
    GuiMenu * addMenu(string name, bool multipleChoice=false, bool autoClose=false);
    template<typename L, typename M>
    GuiMenu * addMenu(string name, vector<string> choices, L *listener, M method, bool multipleChoice=false, bool autoClose=false);
    template<typename L, typename M>
    GuiMenu * addMenu(string name, L *listener, M method, bool multipleChoice=false, bool autoClose=false);

private:
    
    template<typename T>
    void createSliders(GuiElementGroup * elementGroup, Parameter<T> *parameter);
    
    template<typename T>
    void createRangeSliders(GuiElementGroup * elementGroup, string name, Parameter<T> *parameterLow, Parameter<T> *parameterHigh);
    
    template<typename L, typename M>
    void addListenersFromLastElementGroup(L *listener, M method);
    
    void eventWidgetChanged(string & s);
};



template<typename L, typename M>
void GuiWidget::addButton(Parameter<bool> *parameter, L *listener, M method)
{
    addButton(parameter);
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::addButton(string name, bool *value, L *listener, M method)
{
    addButton(new Parameter<bool>(name, value));
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::addButton(string name, L *listener, M method)
{
    addButton(new Parameter<bool>(name, new bool()));
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::addToggle(Parameter<bool> *parameter, L *listener, M method)
{
    addToggle(parameter);
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::addToggle(string name, bool *value, L *listener, M method)
{
    addToggle(new Parameter<bool>(name, value));
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::addToggle(string name, L *listener, M method)
{
    addToggle(new Parameter<bool>(name, new bool()));
    addListenersFromLastElementGroup(listener, method);
}

template<typename T>
void GuiWidget::addSlider(Parameter<T> *parameter)
{
    GuiElementGroup *elementGroup = new GuiElementGroup();
    createSliders(elementGroup, parameter);
    setupElementGroup(elementGroup);
}

template<typename T>
void GuiWidget::addSlider(string name, T *value, T min, T max)
{
    addSlider(new Parameter<T>(name, value, min, max));
}

template<typename T, typename L, typename M>
void GuiWidget::addSlider(Parameter<T> *parameter, L *listener, M method)
{
    addSlider(parameter);
    addListenersFromLastElementGroup(listener, method);
}

template<typename T, typename L, typename M>
void GuiWidget::addSlider(string name, T *value, T min, T max, L *listener, M method)
{
    addSlider(new Parameter<T>(name, value, min, max));
	addListenersFromLastElementGroup(listener, method);
}

template<typename T>
void GuiWidget::addRangeSlider(string name, Parameter<T> *parameterLow, Parameter<T> *parameterHigh)
{
    GuiElementGroup *elementGroup = new GuiElementGroup();
    createRangeSliders(elementGroup, name, parameterLow, parameterHigh);
    setupElementGroup(elementGroup);
}

template<typename T>
void GuiWidget::addRangeSlider(string name, T *valueLow, T *valueHigh, T min, T max)
{
    addRangeSlider(name, new Parameter<T>(name+"-low", valueLow, min, max), new Parameter<T>(name+"-high", valueHigh, min, max));
}

template<typename T, typename L, typename M>
void GuiWidget::addRangeSlider(string name, Parameter<T> *parameterLow, Parameter<T> *parameterHigh, L *listener, M method)
{
    addRangeSlider(name, parameterLow, parameterHigh);
    addListenersFromLastElementGroup(listener, method);
}

template<typename T, typename L, typename M>
void GuiWidget::addRangeSlider(string name, T *valueLow, T *valueHigh, T min, T max, L *listener, M method)
{
    addRangeSlider(name, new Parameter<T>(name+"-low", valueLow, min, max), new Parameter<T>(name+"-high", valueHigh, min, max));
	addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::add2dPad(Parameter<ofPoint> *parameter, L *listener, M method)
{
    add2dPad(parameter);
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::add2dPad(string name, ofPoint *value, ofPoint min, ofPoint max, L *listener, M method)
{
    add2dPad(new Parameter<ofPoint>(name, value, min, max));
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::addColor(string name, ofFloatColor * parameter, ofFloatColor min, ofFloatColor max, L *listener, M method)
{
    addColor(new Parameter<ofFloatColor>(name, parameter, min, max));
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::addColor(string name, ofFloatColor * parameter, L *listener, M method)
{
    addColor(new Parameter<ofFloatColor>(name, parameter, ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1)));
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
void GuiWidget::addColor(Parameter<ofFloatColor> *parameter, L *listener, M method)
{
    addColor(parameter);
    addListenersFromLastElementGroup(listener, method);
}

template<typename L, typename M>
GuiMenu * GuiWidget::addMenu(string name, vector<string> choices, L *listener, M method, bool multipleChoice, bool autoClose)
{
    GuiMenu *menu = new GuiMenu(name, choices, multipleChoice, autoClose);
    menu->setParent(this);
    GuiElementGroup *elementGroup = new GuiElementGroup();
    elementGroup->addElement(menu);
    setupElementGroup(elementGroup);
    ofAddListener(menu->widgetChanged, this, &GuiWidget::eventWidgetChanged);
    ofAddListener(menu->elementEvent, listener, method);
    return menu;
}

template<typename L, typename M>
GuiMenu * GuiWidget::addMenu(string name, L *listener, M method, bool multipleChoice, bool autoClose)
{
    vector<string> choices;
    return addMenu(name, choices, listener, method, multipleChoice, autoClose);
}



////////////////////////////////////////////////////////
//  Add listeners to element groups

template<typename L, typename M>
void GuiWidget::addListenersFromLastElementGroup(L *listener, M method)
{
    for (auto &e : elementGroups[elementGroups.size()-1]->getElements())
    {
        if (e->isWidget())
        {
            vector<GuiElement*> innerElements;
            ((GuiWidgetBase*) e)->getAllElements(innerElements);
            for (auto &ie : innerElements) {
                ofAddListener(ie->elementEvent, listener, method);
            }
        }
        else {
            ofAddListener(e->elementEvent, listener, method);
        }
    }
}



////////////////////////////////////////////////////////
//  Creating elements

template<typename T>
void GuiWidget::createRangeSliders(GuiElementGroup *elementGroup, string name, Parameter<T> *parameterLow, Parameter<T> *parameterHigh)
{
    elementGroup->addElement(new GuiRangeSlider<T>(name, parameterLow, parameterHigh));
}

template<typename T> void GuiWidget::createSliders(GuiElementGroup *elementGroup, Parameter<T> *parameter)
{
    elementGroup->addElement(new GuiSlider<T>(parameter));
}

template<> inline void GuiWidget::createSliders<ofVec2f>(GuiElementGroup *elementGroup, Parameter<ofVec2f> *parameter)
{
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".x", &parameter->getReference()->x, parameter->getMin().x, parameter->getMax().x));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".y", &parameter->getReference()->y, parameter->getMin().y, parameter->getMax().y));
}

template<> inline void GuiWidget::createSliders<ofVec3f>(GuiElementGroup *elementGroup, Parameter<ofVec3f> *parameter)
{
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".x", &parameter->getReference()->x, parameter->getMin().x, parameter->getMax().x));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".y", &parameter->getReference()->y, parameter->getMin().y, parameter->getMax().y));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".z", &parameter->getReference()->z, parameter->getMin().z, parameter->getMax().z));
}

template<> inline void GuiWidget::createSliders(GuiElementGroup *elementGroup, Parameter<ofVec4f> *parameter)
{
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".x", &parameter->getReference()->x, parameter->getMin().x, parameter->getMax().x));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".y", &parameter->getReference()->y, parameter->getMin().y, parameter->getMax().y));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".z", &parameter->getReference()->z, parameter->getMin().z, parameter->getMax().z));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".w", &parameter->getReference()->w, parameter->getMin().w, parameter->getMax().w));
}

template<> inline void GuiWidget::createSliders(GuiElementGroup *elementGroup, Parameter<ofFloatColor> *parameter)
{
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".r", &parameter->getReference()->r, parameter->getMin().r, parameter->getMax().r));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".g", &parameter->getReference()->g, parameter->getMin().g, parameter->getMax().g));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".b", &parameter->getReference()->b, parameter->getMin().b, parameter->getMax().b));
    elementGroup->addElement(new GuiSlider<float>(parameter->getName()+".a", &parameter->getReference()->a, parameter->getMin().a, parameter->getMax().a));
}

template<> inline void GuiWidget::createRangeSliders<ofVec2f>(GuiElementGroup *elementGroup, string name, Parameter<ofVec2f> *parameterLow, Parameter<ofVec2f> *parameterHigh)
{
    elementGroup->addElement(new GuiRangeSlider<float>(name+".x", &parameterLow->getReference()->x, &parameterHigh->getReference()->x, min(parameterLow->getMin().x, parameterHigh->getMin().x), max(parameterLow->getMax().x, parameterHigh->getMax().x)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".y", &parameterLow->getReference()->y, &parameterHigh->getReference()->y, min(parameterLow->getMin().y, parameterHigh->getMin().y), max(parameterLow->getMax().y, parameterHigh->getMax().y)));
}

template<> inline void GuiWidget::createRangeSliders<ofVec3f>(GuiElementGroup *elementGroup, string name, Parameter<ofVec3f> *parameterLow, Parameter<ofVec3f> *parameterHigh)
{
    elementGroup->addElement(new GuiRangeSlider<float>(name+".x", &parameterLow->getReference()->x, &parameterHigh->getReference()->x, min(parameterLow->getMin().x, parameterHigh->getMin().x), max(parameterLow->getMax().x, parameterHigh->getMax().x)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".y", &parameterLow->getReference()->y, &parameterHigh->getReference()->y, min(parameterLow->getMin().y, parameterHigh->getMin().y), max(parameterLow->getMax().y, parameterHigh->getMax().y)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".z", &parameterLow->getReference()->z, &parameterHigh->getReference()->z, min(parameterLow->getMin().z, parameterHigh->getMin().z), max(parameterLow->getMax().z, parameterHigh->getMax().z)));
}

template<> inline void GuiWidget::createRangeSliders<ofVec4f>(GuiElementGroup *elementGroup, string name, Parameter<ofVec4f> *parameterLow, Parameter<ofVec4f> *parameterHigh)
{
    elementGroup->addElement(new GuiRangeSlider<float>(name+".x", &parameterLow->getReference()->x, &parameterHigh->getReference()->x, min(parameterLow->getMin().x, parameterHigh->getMin().x), max(parameterLow->getMax().x, parameterHigh->getMax().x)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".y", &parameterLow->getReference()->y, &parameterHigh->getReference()->y, min(parameterLow->getMin().y, parameterHigh->getMin().y), max(parameterLow->getMax().y, parameterHigh->getMax().y)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".z", &parameterLow->getReference()->z, &parameterHigh->getReference()->z, min(parameterLow->getMin().z, parameterHigh->getMin().z), max(parameterLow->getMax().z, parameterHigh->getMax().z)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".w", &parameterLow->getReference()->w, &parameterHigh->getReference()->w, min(parameterLow->getMin().w, parameterHigh->getMin().w), max(parameterLow->getMax().w, parameterHigh->getMax().w)));
}

template<> inline void GuiWidget::createRangeSliders<ofFloatColor>(GuiElementGroup *elementGroup, string name, Parameter<ofFloatColor> *parameterLow, Parameter<ofFloatColor> *parameterHigh) {
    elementGroup->addElement(new GuiRangeSlider<float>(name+".r", &parameterLow->getReference()->r, &parameterHigh->getReference()->r, min(parameterLow->getMin().r, parameterHigh->getMin().r), max(parameterLow->getMax().r, parameterHigh->getMax().r)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".g", &parameterLow->getReference()->g, &parameterHigh->getReference()->g, min(parameterLow->getMin().g, parameterHigh->getMin().g), max(parameterLow->getMax().g, parameterHigh->getMax().g)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".b", &parameterLow->getReference()->b, &parameterHigh->getReference()->b, min(parameterLow->getMin().b, parameterHigh->getMin().b), max(parameterLow->getMax().b, parameterHigh->getMax().b)));
    elementGroup->addElement(new GuiRangeSlider<float>(name+".a", &parameterLow->getReference()->a, &parameterHigh->getReference()->a, min(parameterLow->getMin().a, parameterHigh->getMin().a), max(parameterLow->getMax().a, parameterHigh->getMax().a)));
}

