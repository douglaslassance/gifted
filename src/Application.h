#pragma once

#include "BeatDetector.h"
#include "MediaPlayer.h"

class Application : public ofBaseApp {

	public:
        void setup();
        void draw();
        void update();
        void stop();
		void audioIn(float * input, int bufferSize, int nChannels);

        ofSoundStream soundStream;
    
        BeatDetector *beatDetector;
        MediaPlayer *mediaPlayer;
};
