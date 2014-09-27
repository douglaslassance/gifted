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
		void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);

        ofSoundStream soundStream;
    
        BeatDetector *beatDetector;
        MediaPlayer *mediaPlayer;
};
