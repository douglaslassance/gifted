#include "Application.h"

void Application::setup() {
    
    ofSetFrameRate(60);
    // Listing our input devices.
    soundStream.listDevices();
    
    // Setting the input device.
    soundStream.setDeviceID(5);
    
    // Starting the stream.
    soundStream.setup(this, 0, 2, 44100, 256, 4);
    soundStream.start();
    
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
    
    // I wonder if this should be either in MediaPlayer of BeatDetector.
    if (beatDetector->isSnare() == true) {
    }
}

void Application::draw(){
    mediaPlayer->draw();
    beatDetector->draw();
}

void Application::audioIn(float * input, int bufferSize, int nChannels) {
    beatDetector->audioIn(input, bufferSize, nChannels);
}
void Application::dragEvent(ofDragInfo dragInfo){
    mediaPlayer->dropped(dragInfo);
}
void Application::keyPressed(int key){
    mediaPlayer->keyPressed(key);
}
void Application::keyReleased(int key){
    mediaPlayer->keyReleased(key);
}
void Application::mousePressed(int x, int y, int button){
    mediaPlayer->mousePressed(x,y,button);
}
void Application::mouseReleased(int x, int y, int button){
    mediaPlayer->mouseReleased(x,y,button);
}
