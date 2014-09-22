#include "gifMasher.h"

void gifMasher::setup(){
    
    // Listing our input devices.
    soundStream.listDevices();
    
    // Setting the input device.
    soundStream.setDeviceID(5);
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;

    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    soundStream.start();
    beatDetect.enableBeatDetect();
}

void gifMasher::stop() {
    beatDetect.disableBeatDetect();
    soundStream.stop();
}

void gifMasher::update(){
}

void gifMasher::draw(){
    std::cout << beatDetect.isKick();
    if (beatDetect.isKick() == true) {
        ofBackground(255, 255, 255);
    } else {
        ofBackground(0, 0, 0);
    }
}

void gifMasher::audioIn(float * input, int bufferSize, int nChannels) {
    beatDetect.audioReceived(input, bufferSize);
}