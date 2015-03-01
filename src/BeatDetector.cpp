#include <iostream>
#include <string>
#include "BeatDetector.h"
#include "ofxBeat.h"

BeatDetector::BeatDetector() {
    kickActive = true;
    snareActive = true;
    hatActive = true;
    isKicking = false;
    isSnaring = false;
    isHatting = false;
    showGUI = true;
    detector.enableBeatDetect();
}

void BeatDetector::stop() {
    detector.disableBeatDetect();
}

bool BeatDetector::isKick() {
    float _kick = detector.kick();
    
    if (_kick < 0.05) {
        isKicking = false;
    }
    
    if (!isKicking and _kick > 0.35 and kickActive) {
        isKicking = true;
        return true;
    }
    
    return false;
}

bool BeatDetector::isSnare() {
    float _snare = detector.snare();
    
    if (_snare < 0.05) {
        isSnaring = false;
    }
    
    if (!isSnaring and _snare > 0.35 and snareActive) {
        isSnaring = true;
        return true;
    }
    
    return false;
}

bool BeatDetector::isHat() {
    float _hat = detector.hihat();
    
    if (_hat < 0.05) {
        isHatting = false;
    }
    
    if (!isHatting and _hat > 0.3 and hatActive) {
        isHatting = true;
        return true;
    }
    
    return false;
}

void BeatDetector::update() {
    detector.update(ofGetElapsedTimeMillis());
}

void BeatDetector::draw() {
    
//    std::stringstream _kick;
//    _kick << detector.kick();
//    std::string __kick = _kick.str();
//    
//    std::stringstream _snare;
//    _snare << detector.snare();
//    std::string __snare = _snare.str();
//
//    std::stringstream _hihat;
//    _hihat << detector.hihat();
//    std::string __hihat = _hihat.str();
    
    if (showGUI) {
        
        if (kickActive) {
            ofDrawBitmapStringHighlight("Kick Detection (K): ON", 10, 160);
            if (isKicking) {
                ofDrawBitmapStringHighlight("TICK", 210, 160);
            }
        } else {
            ofDrawBitmapStringHighlight("Kick Detection (K): OFF", 10, 160);
        }
        
        if (snareActive) {
            ofDrawBitmapStringHighlight("Snare Detection (N): ON",10,180);
            if (isSnaring) {
                ofDrawBitmapStringHighlight("TICK", 210, 180);
            }
        } else {
            ofDrawBitmapStringHighlight("Snare Detection (N): OFF", 10, 180);
        }
    }
}

void BeatDetector::audioIn(float * input, int bufferSize, int nChannels) {
    detector.audioReceived(input, bufferSize, nChannels);
}

void BeatDetector::keyPressed(int key){

    if (key == 107) {
        kickActive = !kickActive;
    
    } else if (key == 110) {
        snareActive = !snareActive;
    
    } else if (key == 117) {
        showGUI = !showGUI;
    }

 }

void BeatDetector::keyReleased(int key){
}

