//
//  MediaPlayer.cpp
//  GifMasher
//
//  Created by matthew radford on 9/21/14.
//
//

#include "MediaPlayer.h"

MediaPlayer::MediaPlayer()
{
    currentImageIndex = 0;
    std::cout << "Starting Instance of Media Player";
    // only allow gifs, search through local data folder
    ofDirectory dir("");
    dir.allowExt("gif");
    dir.listDir();
    // looping through directory adding gifs. do this on another thread.
    for(int i = 0; i < dir.numFiles(); i++){
        cout << " found a gif : "<<dir.getPath(i) << "\n";
        this->decoder.decode(dir.getPath(i));
        images.push_back(this->decoder.getFile());
    }
    maxImages = images.size()-1;
    imageFrame = 1;
    newImage();
    updateBounds();
    // if false, will attempt to preserve aspect ratio a bit
    stretch = true;
};

void MediaPlayer::newImage(){
    // picks a new image of gifs from the array
    
    frameClock = 0.0;
    if (currentImageIndex +1 <=maxImages){
        currentImageIndex+=1;
    }else{
        currentImageIndex =0;
    }
    currentImage = images[currentImageIndex];
    imageFrame = 0;
    maxImageFrame = currentImage.getNumFrames();
    newFrame();
}

void MediaPlayer::updateBounds(){
    boundHeight = ofGetHeight();
    boundWidth = ofGetWidth();
}
void MediaPlayer::newFrame(){
    // gets new frame of the gif animation
    // frame duration is the amount of time this frame should take
    imageFrame+=1;
    frameDuration = currentImage.getDuration();
    
}

Boolean MediaPlayer::frameExpired(){
    if (frameClock > frameDuration){
        frameClock = 0;
        return true;
    }else{
        return false;
    }
}

void MediaPlayer::calculateDimensions(){

    if (stretch == true){
        frameWidth = boundWidth;
        frameHeight = boundHeight;
    }else{
        frameWidth = boundHeight * currentImage.getWidth() / currentImage.getHeight();
        frameHeight = boundHeight;
        if (frameWidth < boundWidth){
            frameWidth = boundWidth;
        }
    }

}
void MediaPlayer::update(){
    // handles calculating the stretch values for the gif to be drawn
    // and the dimension of the bound frame in which it will draw into
    // by default thi bound frame is the of window
    updateBounds();
    calculateDimensions();
    timedelta = ofGetLastFrameTime();
    frameClock+=timedelta;
    
    // use these prints to debug various parts of the code
    //cout<< "clock = "<<frameClock << "\n";
    //cout<< "duration = "<< frameDuration << "\n";
    //cout << "imageSize = " << currentImage.getWidth() << " X "<< currentImage.getHeight() << "\n";
    //cout << "boundSize = " << boundWidth << " x " << boundHeight << "\n";
    if (frameExpired() == true){
        newFrame();
    }
    if (imageFrame > maxImageFrame){
        newImage();
    }
}

void MediaPlayer::draw(){
    currentImage.drawFrame(imageFrame,0,0,frameWidth,frameHeight);
}