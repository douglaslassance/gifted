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
        void keyReleased(int key);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void setAudioInput(int index);
        ofSoundStream soundStream;
        int audioDeviceID;
        BeatDetector *beatDetector;
        MediaPlayer *mediaPlayer;
};
