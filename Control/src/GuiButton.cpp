#include "GuiButton.h"

GuiButtonBase::GuiButtonBase(Parameter<bool> *parameter) : GuiElement(parameter->getName())
{
    this->parameter = parameter;
    initializeButton();
}

GuiButtonBase::GuiButtonBase(string name, bool *value) : GuiElement(name)
{
    parameter = new Parameter<bool>(name, value);
    initializeButton();
}

GuiButtonBase::GuiButtonBase(string name) : GuiElement(name)
{
    parameter = new Parameter<bool>(name, new bool());
    initializeButton();
}

GuiButtonBase::~GuiButtonBase()
{
    delete parameter;
}

void GuiButtonBase::initializeButton()
{
    setValue(parameter->get());
    lerpFrame = 0;
    lerpNumFrames = 0;
    lerpNextValue = 0.0;
    setLeftJustified(false);
    changed = false;
}

void GuiButtonBase::updateParameterOscAddress()
{
    parameter->setOscAddress(getAddress());
}

void GuiButtonBase::setValue(bool value, bool sendChangeNotification)
{
    bool previous = parameter->get();
    changed = (value != previous);
    parameter->set(value);
    if (sendChangeNotification && changed)
    {
        GuiButtonEventArgs args(this, value);
        ofNotifyEvent(buttonEvent, args, this);
    }
}

void GuiButtonBase::lerpTo(float nextValue, int numFrames)
{
    this->lerpNextValue = nextValue;
    this->lerpNumFrames = numFrames;
    lerpFrame = 0;
}

void GuiButtonBase::getParameters(vector<ParameterBase*> & parameters)
{
    parameters.push_back(parameter);
}

void GuiButtonBase::setValueFromSequence(Sequence &sequence)
{
    setValue(sequence.getValueAtCurrentIndex() > 0.5, true);
}

void GuiButtonBase::setSequenceFromValue(Sequence &sequence, int column)
{
    sequence.setValueAtCell(column, parameter->get() > 0.5);
}

void GuiButtonBase::setSequenceFromExplicitValue(Sequence &sequence, int column, float value)
{
    sequence.setValueAtCell(column, value > 0.5);
}

bool GuiButtonBase::getValue()
{
    return parameter->get();
}

void GuiButtonBase::update()
{
    if (lerpFrame < lerpNumFrames)
    {
        lerpFrame++;
        if (lerpFrame == lerpNumFrames) {
            setValue(lerpNextValue > 0.5, true);
        }
    }
}

void GuiButtonBase::draw()
{
	ofPushStyle();
    
    ofFill();
    ofSetLineWidth(1);
    parameter->get() ? ofSetColor(colorForeground) : ofSetColor(colorBackground);
    ofRect(rectangle);
    
    ofNoFill();
    ofSetColor(colorOutline);
    ofRect(rectangle);
    
	if (mouseOver)
	{
	    ofNoFill();
	    ofSetLineWidth(2);
	    ofSetColor(colorActive);
	    ofRect(rectangle);
        ofSetLineWidth(1);
	}
    
    ofSetColor(colorText);
    ofDrawBitmapString(display,
                       rectangle.x + (leftJustified ? 4 : 0.5 * (rectangle.width - stringWidth)),
                       rectangle.y + 0.5 * (rectangle.height + 0.5 * stringHeight) + 1);

	ofPopStyle();
}

void GuiButtonBase::setupGuiPositions()
{
    GuiElement::setupGuiPositions();
    stringWidth = ofBitmapStringGetBoundingBox(display, 0, 0).width;
    stringHeight = ofBitmapStringGetBoundingBox(display, 0, 0).height;
}

void GuiButtonBase::getXml(ofXml &xml)
{
    xml.addValue<bool>("Value", getValue());
}

void GuiButtonBase::setFromXml(ofXml &xml)
{
    setValue(xml.getValue<bool>("Value"), true);
}

void GuiButton::addElementToTouchOscLayout(TouchOscPage *page, float *y)
{
    TouchOscButton *button = page->addButton(getName(), 0.05, *y, 0.9, 1);
    TouchOscLabel *label = page->addLabel(getName(), 0.05, *y, 0.9, 1);
    button->setOscAddress(parameter->getOscAddress());
    label->setType(0);
    label->setColor(RED);
    *y += 1.04;
}

void GuiToggle::addElementToTouchOscLayout(TouchOscPage *page, float *y)
{
    TouchOscToggle *toggle = page->addToggle(getName(), 0.05, *y, 0.9, 1);
    TouchOscLabel *label = page->addLabel(getName(), 0.05, *y, 0.9, 1);
    toggle->setOscAddress(parameter->getOscAddress());
    label->setType(0);
    label->setColor(RED);
    *y += 1.05;
}

void GuiButtonBase::addElementToTouchOscLayout(TouchOscPage *page, float *y)
{

}

string GuiButtonBase::getOscAddress()
{
    return parameter->getOscAddress();
}

void GuiButtonBase::sendOsc(ofxOscMessage &msg)
{
    msg.addIntArg(parameter->get() ? 1 : 0);
}

void GuiButtonBase::receiveOsc(ofxOscMessage &msg)
{
    setValue(msg.getArgAsInt32(0) > 0.5);
}

bool GuiButtonBase::valueChanged()
{
    if (changed) {
        changed = false;
        return true;
    }
    else {
        return false;
    }
}

bool GuiButton::mousePressed(int mouseX, int mouseY)
{
    if (mouseOver)
    {
        setValue(true, true);
        return true;
    }
    return false;
}

bool GuiButton::mouseReleased(int mouseX, int mouseY)
{
    GuiElement::mouseReleased(mouseX, mouseY);
    if (getValue())
    {
        setValue(false, false);
        return true;
    }
    else {
        return false;
    }
}

bool GuiToggle::mousePressed(int mouseX, int mouseY)
{
    if (mouseOver)
    {
        bool value = !parameter->get();
        setValue(value, true);
        return true;
    }
    else {
        return false;
    }
}

bool GuiButton::keyPressed(int key)
{
    if (mouseOver && key==' ')
    {
        setValue(true, true);
        setValue(false, false);
        return true;
    }
    else {
        return false;
    }
}

bool GuiToggle::keyPressed(int key)
{
    if (mouseOver && key==' ')
    {
        bool value = !parameter->get();
        setValue(value, true);
        return true;
    }
    else {
        return false;
    }
}

