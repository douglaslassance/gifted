#include "BeatDetector.h"

BeatDetector::BeatDetector() {
    bd.enableBeatDetect();
}

void BeatDetector::stop() {
    bd.disableBeatDetect();
}

bool BeatDetector::isSnare() {
    return bd.isSnare();
}

void BeatDetector::update() {
    bd.updateFFT();
}

void BeatDetector::draw() {
    if (bd.isSnare() == true) {
        ofDrawBitmapStringHighlight("SNARE",20,20);
    }
    if (bd.isHat() == true){
        ofDrawBitmapStringHighlight("HAT",20,40);
    }
    if (bd.isKick() == true){
        ofDrawBitmapStringHighlight("KICK",20,60);
    }
}

void BeatDetector::audioIn(float * input, int bufferSize, int nChannels) {
    //bd.audioReceived(input, bufferSize);
}
