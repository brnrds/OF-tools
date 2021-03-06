#include "DebugScreen.h"


void DebugScreen::setup(int width, int height, bool clearControls)
{
    Scene::setup(width, height, clearControls);

    color1 = ofFloatColor(ofRandom(1), ofRandom(1), ofRandom(1), 1);
    color2 = ofFloatColor(ofRandom(1), ofRandom(1), ofRandom(1), 1);
    numRects = 8;
    speed = 60;

    vector<string> debugModes;
    debugModes.push_back("Full");
    debugModes.push_back("Gradient");
    debugModes.push_back("Checkerboard");
    debugModes.push_back("Frames");

    vector<string> gradientModes;
    gradientModes.push_back("Circular");
    gradientModes.push_back("Linear");
    gradientModes.push_back("Bar");

    control.addMenu("mode", debugModes, this, &DebugScreen::setType);
    //control.addColor("color1", &color1, this, &DebugScreen::refresh);
    //control.addColor("color2", &color2, this, &DebugScreen::refresh);
    control.addSlider("numRects", &numRects, 1, 100);
    control.addSlider("speed", &speed, 0, 100);
    control.addMenu("gradient type", gradientModes, this, &DebugScreen::setupGradient);
    
    GuiMenuEventArgs evt(NULL, 0, 0);
    setupGradient(evt);
}

void DebugScreen::setType(GuiMenuEventArgs &e)
{
    if      (e.index == 0)           type = FULL;
    else if (e.index == 1)       type = GRADIENT;
    else if (e.index == 2)   type = CHECKERBOARD;
    else if (e.index == 3)         type = FRAMES;
}

void DebugScreen::update()
{
}

void DebugScreen::draw(int x, int y)
{
    Scene::beginDraw(x, y);

    if (type == FULL) {
        drawFull();
    }
    else if (type == CHECKERBOARD) {
        drawCheckerboard();
    }
    else if (type == FRAMES) {
        drawFrames();
    }
    else if (type == GRADIENT) {
        drawGradient();
    }

    Scene::endDraw();
}

void DebugScreen::drawFull()
{
    ofSetColor(color1);
    ofFill();
    ofRect(0, 0, width, height);
}

void DebugScreen::drawCheckerboard()
{
    ofSetColor(color2);
    ofRect(0, 0, width, height);
    
    float x, y, w, h;
    w = width / numRects;
    h = height / numRects;
    
    ofSetColor(color1);
    for (int i=0; i<numRects; i++){
        for (int j=0; j<numRects; j++) {
            if ((i+j)%2==0) continue;
            x = ofMap(i, 0, numRects, 0, width);
            y = ofMap(j, 0, numRects, 0, height);
            ofRect(x, y, w, h);
        }
    }
}

void DebugScreen::drawFrames()
{
    ofSetColor(color1);
    ofNoFill();
    ofSetLineWidth((float) width/ numRects);
    
    float x, y, w, h, di;
    if (speed == 0) di = 0;
    else    di = (ofGetFrameNum() % speed) / (float)speed;
    for (int i=0; i<numRects; i++)
    {
        x = ofMap(i + di, 0, numRects, 0, width/2.0);
        y = ofMap(i + di, 0, numRects, 0, height/2.0);
        w = ofMap(i + di, 0, numRects, width, 0);
        h = ofMap(i + di, 0, numRects, height, 0);
        ofRect(x, y, w, h);
    }

    ofSetLineWidth(12);
    ofSetColor(color2);
    ofRect(6, 6, width-12, height-12);
}

void DebugScreen::drawGradient()
{
    GLboolean depthMaskEnabled;
    glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMaskEnabled);
    glDepthMask(GL_FALSE);
    gradientMesh.draw();
    if (depthMaskEnabled){
        glDepthMask(GL_TRUE);
    }
}

void DebugScreen::refresh(GuiButtonEventArgs &e)
{
    if (type == GRADIENT)
    {
        GuiMenuEventArgs args(NULL, 0, true);
        setupGradient(args);
    }
}

void DebugScreen::setupGradient(GuiMenuEventArgs &evt)
{
    this->gradientMode = evt.index;

    gradientMesh.clear();
    gradientMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    gradientMesh.setUsage(GL_STREAM_DRAW);
    
    if (gradientMode == 0)  // circuluar
    {
        ofVec2f center(width / 2, height / 2);
        gradientMesh.addVertex(center);
        gradientMesh.addColor(ofColor(color1));
        int n = 64;
        float angleBisector = TWO_PI / (n * 2);
        float smallRadius = ofDist(0, 0, width / 2, height / 2);
        float bigRadius = smallRadius / cos(angleBisector);
        for(int i = 0; i <= n; i++) {
            float theta = i * TWO_PI / n;
            gradientMesh.addVertex(center + ofVec2f(sin(theta), cos(theta)) * bigRadius);
            gradientMesh.addColor(ofColor(color2));
        }
    }
    else if (gradientMode == 1) // linear
    {
        gradientMesh.addVertex(ofVec2f(0, 0));
        gradientMesh.addVertex(ofVec2f(width, 0));
        gradientMesh.addVertex(ofVec2f(width, height));
        gradientMesh.addVertex(ofVec2f(0, height));
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color2));
    }
    else if (gradientMode == 2) // bar
    {
        gradientMesh.addVertex(ofVec2f(width / 2, height / 2));
        gradientMesh.addVertex(ofVec2f(0, height / 2));
        gradientMesh.addVertex(ofVec2f(0, 0));
        gradientMesh.addVertex(ofVec2f(width, 0));
        gradientMesh.addVertex(ofVec2f(width, height / 2));
        gradientMesh.addVertex(ofVec2f(width, height));
        gradientMesh.addVertex(ofVec2f(0, height));
        gradientMesh.addVertex(ofVec2f(0, height / 2));
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color1));
    }
}
