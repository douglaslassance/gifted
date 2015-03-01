#include "Application.h"

void Application::setup() {
    
    // Setting the frame rate.
    ofSetFrameRate(60);
    
    // Setting the background color.
    ofBackground(0, 0, 0);
    
    // Listing our input devices.
    soundStream.listDevices();
    
    // Setting the input device.
    setAudioInput(0);
    
    // Initializing main objects.
    mediaPlayer = new MediaPlayer();
    beatDetector = new BeatDetector();
}

void Application::stop() {
    beatDetector->stop();
    soundStream.stop();
}

void Application::update() {
    beatDetector->update();
    mediaPlayer->update();
    
    if (beatDetector->isKick() or beatDetector->isSnare()) {
        mediaPlayer->switchMedia(10);
    }
}

void Application::draw() {
    mediaPlayer->draw();
    beatDetector->draw();
    ofDrawBitmapStringHighlight("Audio Input (0-9): " + ofToString(audioDeviceID), 10, 140);
}

void Application::setAudioInput(int index) {
    cout << "Setting audio input to " << index << ".\n";
    audioDeviceID = index;
    soundStream.close();
    soundStream.setDeviceID(index);
    soundStream.setup(this, 0, 2, 44100, 1024, 4);
}

void Application::audioIn(float* input, int bufferSize, int nChannels) {
    beatDetector->audioIn(input, bufferSize, nChannels);
}
void Application::dragEvent(ofDragInfo dragInfo){
    mediaPlayer->dropped(dragInfo);
}
void Application::keyPressed(int key){
    
    for (int code = 48; code <= 57; code++) {
        if (key==code) {
            setAudioInput(key-48);
        }
    }
    
    mediaPlayer->keyPressed(key);
    beatDetector->keyPressed(key);
}
void Application::keyReleased(int key){
    mediaPlayer->keyReleased(key);
    beatDetector->keyReleased(key);
}
void Application::mousePressed(int x, int y, int button){
    mediaPlayer->mousePressed(x,y,button);
}
void Application::mouseReleased(int x, int y, int button){
    mediaPlayer->mouseReleased(x,y,button);
}
