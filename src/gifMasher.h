#pragma once

#include <iostream>
#include "ofMain.h"
#include "beatDetect.h"

class gifMasher : public ofBaseApp {

	public:
        void setup();
        void draw();
        void update();
        void stop();
		void audioIn(float * input, int bufferSize, int nChannels);
    
        vector <float> left;
        vector <float> right;
        vector <float> volHistory;
    
        int bufferCounter;
        int drawCounter;
    
        float smoothedVol;
        float scaledVol;
    
        ofSoundStream soundStream;
        beatDetect beatDetect;
};
