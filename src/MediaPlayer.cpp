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
    std::cout << "Starting Instance of Media Player";
    mediaIndex = 0;
    // if false, will attempt to preserve aspect ratio a bit
    stretch = true;
    frameOffsetX = 0.0;
    frameOffsetY = 0.0;
    flushQue();
    loadGifs("");
};


void MediaPlayer::loadGifs(string path){
    
    // only allow gifs, search through local data folder
    ofDirectory dir(path);
    dir.allowExt("gif");
    dir.listDir();
    // looping through directory adding gifs. do this on another thread pleeeeeease.
    for(int i = 0; i < dir.numFiles(); i++){
        string gif =dir.getPath(i);
        que.push_back(gif);
        cout << "queing gif: "<< gif<<"\n";
    }

}

void MediaPlayer::loadGif(string name){
        ofVideoPlayer *movie;
        movie = new ofVideoPlayer();
        movie->loadMovie(name);
        cout << "loading gif: "<<name << "\n";
        media.push_back(movie);

}
void MediaPlayer::loadFromQue(int index){
    queing = true;
    loadGif(que[index]);
    queFileName = que[index];
    queIndex += 1;
    if (queIndex +1 >= que.size()){
        resetQue();
    }
}
void MediaPlayer::flushQue(){
    que.clear();
    queIndex = 0;
    queFileName = "";
}
void MediaPlayer::resetQue(){
    queing = false;
    queIndex = 0;
    queFileName = "";
    que.clear();
    quefinished();
}
void MediaPlayer::quefinished(){
        switchMedia();
}

void MediaPlayer::updateBounds(){
    boundHeight = ofGetHeight();
    boundWidth = ofGetWidth();
}


void MediaPlayer::switchMedia(){
        media[mediaIndex]->stop();
        media[mediaIndex]->setPosition(0.0);
        mediaIndex +=1;
        if (mediaIndex > media.size()-1){
            mediaIndex = 0;
        }
        media[mediaIndex]->play();
        media[mediaIndex]->update();
}
void MediaPlayer::calculateDimensions(){

    if (stretch == true){
        frameWidth = boundWidth;
        frameHeight = boundHeight;
    }else{
        frameWidth = boundHeight * media[mediaIndex]->getWidth() / media[mediaIndex]->getHeight();
        frameOffsetX = (boundWidth - frameWidth) * .5;
        frameHeight = boundHeight;
        if (frameWidth < boundWidth){
            frameHeight = boundWidth * media[mediaIndex]->getHeight() / media[mediaIndex]->getWidth();
            frameWidth = boundWidth;
            frameOffsetX = (boundWidth - frameWidth) * .5;

        }
    }

}
void MediaPlayer::update(){
    if (que.size() > 0){
        loadFromQue(queIndex);
    }else{
        if (media.size() >= mediaIndex+1){
            calculateDimensions();
            timedelta = ofGetLastFrameTime();
            media[mediaIndex]->update();
            if (media[mediaIndex]->getPosition() >=.97){
                switchMedia();
            }
        }
    }
    updateBounds();

}

void MediaPlayer::dropped(ofDragInfo dragInfo){
    flushQue();
    for (int i = 0; i < dragInfo.files.size();i++){
        if (ofIsStringInString(dragInfo.files[i], ".gif") == false){
            loadGifs(dragInfo.files[i]);
        }else{
            que.push_back(dragInfo.files[i]);
        }
        cout << "dropped : "<<dragInfo.files[i] << "\n";
    }
    
}
void MediaPlayer::draw(){
    if (que.size() > 0){
        ofDrawBitmapStringHighlight("loading gif: " +ofToString(queFileName) + "   "+ofToString(queIndex+1) + " / "+ofToString(que.size()), 20,20);
    }else{
        if (media.size() >= mediaIndex+1){
            media[mediaIndex]->draw(frameOffsetX, frameOffsetY, frameWidth, frameHeight);
            ofDrawBitmapStringHighlight("File Name: "+ ofToString(media[mediaIndex]->getMoviePath()), 10,20);
            ofDrawBitmapStringHighlight("Playback Position: "+ ofToString(media[mediaIndex]->getPosition())+" / 1.0", 10,40);
            ofDrawBitmapStringHighlight("index: "+ ofToString(mediaIndex+1)+" / "+ofToString(media.size()), 10,60);

        }else{
            ofDrawBitmapStringHighlight("NO GIFS LOADED", boundWidth/2-100,boundHeight/2);
            ofDrawBitmapStringHighlight("drag and drop files, or a folder", boundWidth/2-170,boundHeight/2+40);

        }
    }
}

void MediaPlayer::keyPressed(int key){
    
}
void MediaPlayer::mousePressed(int x, int y, int button){
    
}
void MediaPlayer::mouseReleased(int x, int y, int button){
    
}