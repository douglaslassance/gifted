#include "Application.h"

void Application::setup() {
    
    ofSetFrameRate(30);
    // Listing our input devices.
    soundStream.listDevices();
    
    // Setting the input device.
    soundStream.setDeviceID(3);
    
    // Starting the stream.
    soundStream.setup(this, 0, 2, 44100, 1024, 4);
    
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
        mediaPlayer->switchMedia(1);
    }
}

void Application::draw(){
    mediaPlayer->draw();
    beatDetector->draw();
}

void Application::audioIn(float* input, int bufferSize, int nChannels) {
    beatDetector->audioIn(input, bufferSize, nChannels);
}
void Application::dragEvent(ofDragInfo dragInfo){
    mediaPlayer->dropped(dragInfo);
}
void Application::keyPressed(int key){
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
