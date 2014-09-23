//
//  mediaPlayer.h
//  GifMasher
//
//  Created by matthew radford on 9/21/14.
//
//


#include "gifMasher.h"
#include "ofxGifDecoder.h"
#include "ofxGifFile.h"


#ifndef _MediaPlayer
#define _MediaPlayer

class MediaPlayer{
    
public:
    void update();
    void draw();
    void newImage();
    void newFrame();
    void calculateDimensions();
    void updateBounds();
    Boolean frameExpired();
    Boolean stretch;
    int maxImages;
    int currentImageIndex;
    float timedelta;
    int imageFrame;
    float frameDuration;
    int maxImageFrame;
    float frameClock;
    float frameHeight;
    float frameWidth;
    float boundWidth;
    float boundHeight;
    vector<ofxGifFile> images;
    ofxGifDecoder decoder;
    ofxGifFile currentImage;
 
    MediaPlayer();
    
};

#endif
