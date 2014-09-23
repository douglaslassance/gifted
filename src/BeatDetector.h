#ifndef __GifMasher__beatDetector__
#define __GifMasher__beatDetector__

#include "beatDetect.h"

class BeatDetector{

public:
    
    BeatDetector();

    void setup();
    void draw();
    void stop();
    void update();
    bool isSnare();
    void audioIn(float * input, int bufferSize, int nChannels);
    
    beatDetect bd;
};

#endif
