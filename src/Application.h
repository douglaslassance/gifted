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
        void dragEvent(ofDragInfo dragInfo);

        ofSoundStream soundStream;
    
        BeatDetector *beatDetector;
        MediaPlayer *mediaPlayer;
};
