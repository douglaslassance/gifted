#include "gifMasher.h"

void gifMasher::setup(){
    mediaPlayer = new MediaPlayer();
    ofSetFrameRate(30);
    
    // Listing our input devices.
    soundStream.listDevices();
    
    // Setting the input device.
    soundStream.setDeviceID(3);
    
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

void gifMasher::update() {
    beatDetect.updateFFT();
    mediaPlayer->update();
    if (beatDetect.isSnare() == true) {
        mediaPlayer->newImage();
    }
}

void gifMasher::draw(){

    mediaPlayer->draw();
    if (beatDetect.isSnare() == true) {
        ofDrawBitmapStringHighlight("SNARE",20,20);
    }
    if (beatDetect.isHat() == true){
        ofDrawBitmapStringHighlight("HAT",20,40);
    }
    if (beatDetect.isKick() == true){
        ofDrawBitmapStringHighlight("KICK",20,60);
    }
}

void gifMasher::audioIn(float * input, int bufferSize, int nChannels) {
    beatDetect.audioReceived(input, bufferSize);

}