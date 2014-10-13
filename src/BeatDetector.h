#ifndef __GifMasher__beatDetector__
#define __GifMasher__beatDetector__

#include <iostream>
#include <string>
#include "ofxBeat.h"

class BeatDetector{

public:
    
    BeatDetector();
    
    void setup();
    void draw();
    void stop();
    void update();
    bool isSnare();
    bool isKick();
    bool isHat();
    void keyPressed(int key);
    void keyReleased(int key);
    void audioIn(float* input, int bufferSize, int nChannels);

private:
    
    bool kickActive;
    bool snareActive;
    bool hatActive;
    
    bool isKicking;
    bool isSnaring;
    bool isHatting;
    
    bool showGUI;
    
    ofxBeat detector;
    
};

#endif
