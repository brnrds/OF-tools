#pragma once

#include "ofBitmapFont.h"
#include "Parameter.h"
#include "GuiElement.h"
#include "GuiSlider.h"


class GuiMultiElement : public GuiElement
{
public:
    
    GuiMultiElement(string name);
    virtual ~GuiMultiElement();
    
    virtual bool isMultiElement() {return true;}
    virtual bool isMenu() {return false;}
    
    vector<GuiElement*> & getElements() {return elements;}
    GuiElement * getElement(string name);
    
    virtual void getParameters(vector<ParameterBase*> & parameters_);

    bool removeElement(string name);
    void clearElements();
    
    void setHeader(string header);
    void setCollapsible(bool collapsible);
    
    bool getCollapsible() {return collapsible;}
    bool getCollapsed();
    void setCollapsed(bool collapsed);

    bool mouseMoved(int mouseX, int mouseY);
    bool mousePressed(int mouseX, int mouseY);
    bool mouseReleased(int mouseX, int mouseY);
    bool mouseDragged(int mouseX, int mouseY);
    bool keyPressed(int key);

    void setHeaderColor(ofColor headerColor) {this->headerColor = headerColor;}
    void setHeaderHeight(int headerHeight) {this->headerHeight = headerHeight;}
    void setControllerHeight(int controllerHeight) {this->controllerHeight = controllerHeight;}
    void setMarginX(int marginX) {this->marginX = marginX;}
    void setMarginY(int marginY) {this->marginY = marginY;}

    ofColor getHeaderColor() {return headerColor;}
    int getHeaderHeight() {return headerHeight;}
    int getControllerHeight() {return controllerHeight;}
    int getMarginX() {return marginX;}
    int getMarginY() {return marginY;}
    
    virtual void update();
    virtual void draw();
    
    void getXml(ofXml &xml);
    void setFromXml(ofXml &xml);
    
    ofEvent<GuiElement*> newElementEvent;
    ofEvent<GuiElement*> removeElementEvent;
    
protected:
    
    void setupGuiPositions();
    void addElementToTouchOscLayout(TouchOscPage *page, float *y);
    void updateParameterOscAddress();
    virtual void initializeElement(GuiElement *element, bool sendNotification=true);
    
    vector<GuiElement*> elements;

    // header
    ofRectangle headerRectangle;
    string header;
    bool headerActive;
    bool collapsible, collapsed;
    float headerStringHeight;
    bool draggingWidget;
    
    // style
    ofColor headerColor;
    int headerHeight;
    int controllerHeight;
    int marginX;
    int marginY;
};
