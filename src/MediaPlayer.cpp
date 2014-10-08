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
    frameOffsetX = 0.0;
    frameOffsetY = 0.0;
    addingToGroup = false;
    flushQue();
    loopingIndex = 2;
    stretchIndex = 0;
    drawUI = true;
    groups.reserve(100);
};


void MediaPlayer::loadGifs(string path,MediaGroup* group){
    // only allow gifs, search through local data folder
    ofDirectory dir(path);
    dir.allowExt("gif");
    dir.listDir();
    // looping through directory adding gifs. do this on another thread pleeeeeease.
    for(int i = 0; i < dir.numFiles(); i++){
        string gif =dir.getPath(i);
        loadSingleGif(gif, group);
        cout << "queing gif: "<< gif<<"\n";
    }

}

void MediaPlayer::loadSingleGif(string path, MediaGroup* group){
    que.push_back(path);
}
void MediaPlayer::loadGif(string name){
        ofVideoPlayer *movie;
        movie = new ofVideoPlayer();
    
        movie->loadMovie(name);
        groups[groupIndex]->media.push_back(movie);

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
    queing = true;
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
        switchMedia(1);
}

void MediaPlayer::updateBounds(){
    boundHeight = ofGetHeight();
    boundWidth = ofGetWidth();
}

void MediaPlayer::manageLooping(){
    if (lastLoopingIndex != loopingIndex){

        if (loopingIndex > 3){
            loopingIndex = 1;
        }
        if (loopingIndex <=0){
            loopingIndex =3;
        }
        
        if (loopingIndex == 1){
            // here it will stop on last frme
            groups[groupIndex]->media[mediaIndex]->setLoopState(OF_LOOP_NONE);
            groups[groupIndex]->media[mediaIndex]->play();
            
        }
        if (loopingIndex == 2){
            // start back on first frame
            groups[groupIndex]->media[mediaIndex]->setLoopState(OF_LOOP_NORMAL);
            
        }
        if (loopingIndex == 3){
            //get to last frame, then ping pong back and forth
            groups[groupIndex]->media[mediaIndex]->setLoopState(OF_LOOP_PALINDROME);
            
        }
    }

}
void MediaPlayer::shuffleMedia(){
    std::random_shuffle(groups[groupIndex]->media.begin(), groups[groupIndex]->media.end());
}

void MediaPlayer::shuffleFrame(){
    groups[groupIndex]->media[mediaIndex]->setPosition(ofRandom(0,1));
}
void MediaPlayer::resetMedia(){
    groups[groupIndex]->media[mediaIndex]->stop();
    groups[groupIndex]->media[mediaIndex]->setPosition(0.0);
    mediaIndex = 0;
    shuffleMedia();
    groups[groupIndex]->media[mediaIndex]->play();
    groups[groupIndex]->media[mediaIndex]->update();

}
void MediaPlayer::switchMedia(int amt){
    calculateDimensions();
    if (groups.size()) {
        groups[groupIndex]->media[mediaIndex]->stop();
        groups[groupIndex]->media[mediaIndex]->setPosition(0.0);
        mediaIndex +=amt;
        if (mediaIndex > groups[groupIndex]->media.size()-1){
            mediaIndex = 0;
            shuffleMedia();
        }
        if (mediaIndex < 0){
            mediaIndex =groups[groupIndex]->media.size()-1;
            shuffleMedia();
        }
        shuffleFrame();
        groups[groupIndex]->media[mediaIndex]->play();
        groups[groupIndex]->media[mediaIndex]->update();
    }

}
void MediaPlayer::calculateDimensions(){

    
    if (stretchIndex == 0){
        // traditional stretching
        frameWidth = boundWidth;
        frameHeight = boundHeight;
        stretchMode = "stretch";
        frameOffsetX = 0;
        frameOffsetY = 0;
    }else if (stretchIndex == 1){
        // stretching accounting for the aspect ratio
        frameWidth = boundHeight * groups[groupIndex]->media[mediaIndex]->getWidth() / groups[groupIndex]->media[mediaIndex]->getHeight();
        frameOffsetX = (boundWidth - frameWidth) * .5;
        frameHeight = boundHeight;
        if (frameWidth < boundWidth){
            frameHeight = boundWidth * groups[groupIndex]->media[mediaIndex]->getHeight() / groups[groupIndex]->media[mediaIndex]->getWidth();
            frameWidth = boundWidth;
            frameOffsetX = (boundWidth - frameWidth) * .5;

        }
        frameOffsetY = 0;
        stretchMode = "preserve";
    }else if (stretchIndex == 2){
        //fitting it to the screen
        if (groups[groupIndex]->media[mediaIndex]->getWidth() > groups[groupIndex]->media[mediaIndex]->getHeight()){
            float difference = boundWidth/ groups[groupIndex]->media[mediaIndex]->getWidth();
            frameWidth = groups[groupIndex]->media[mediaIndex]->getWidth() * difference;
            frameHeight = groups[groupIndex]->media[mediaIndex]->getHeight()*difference;
            frameOffsetX = 0;
            frameOffsetY = (boundHeight - frameHeight) * .5;
        }
        if ( frameHeight > boundHeight){
            float difference = boundHeight/groups[groupIndex]->media[mediaIndex]->getHeight();
            frameHeight =groups[groupIndex]->media[mediaIndex]->getHeight() * difference;
            frameWidth = groups[groupIndex]->media[mediaIndex]->getWidth() * difference;
            frameOffsetX = (boundWidth - frameWidth)*.5;
            frameOffsetY = (boundHeight - frameHeight)*.5;
            
        }
        stretchMode = "fit";

    }

}
void MediaPlayer::update(){
    updateBounds();
    if (que.size() > 0){
        loadFromQue(queIndex);
    }else{
        if (groups.size() > 0){
            calculateDimensions();
            if (groups[groupIndex]->media.size() >= mediaIndex+1){
                manageLooping();
                timedelta = ofGetLastFrameTime();
                if (loopingIndex == 1){
                    if (groups[groupIndex]->media[mediaIndex]->getPosition() > .96){
                        cout << "media done";
                        switchMedia(1);
                    }
                }
                groups[groupIndex]->media[mediaIndex]->update();
            }
        }
    }

}

void MediaPlayer::makeGroup(string name){
    mediaIndex =0;
    MediaGroup *group;
    group = new MediaGroup(groups.size(),name);
    groups.push_back(group);
    groupIndex = group->identity;
    cout << "GROUP IDENTITY: " << groupIndex;
    return;
}

void MediaPlayer::dropped(ofDragInfo dragInfo){
    queing = true;
    flushQue();
    if (addingToGroup == true){
    }else{
        makeGroup("GROUP "+ofToString(groups.size()));
    }

    groups[groupIndex]->media.reserve(dragInfo.files.size());
    que.reserve(dragInfo.files.size());
    
    for (int i = 0; i < dragInfo.files.size();i++){
        if (ofIsStringInString(dragInfo.files[i], ".gif") == false){
            loadGifs(dragInfo.files[i],groups[groupIndex]);
        }else{
            loadSingleGif(dragInfo.files[i],groups[groupIndex]);
        }
    }
    
}
void MediaPlayer::changeMediaForwards(){
    if (mediaIndex+1 >=groups[groupIndex]->media.size()){
        mediaIndex = 0;
    }else{
        mediaIndex+=1;
    }
    groups[groupIndex]->media[mediaIndex]->play();
}
void MediaPlayer::changeMediaBackwards(){
    if (mediaIndex-1 < 0){
        mediaIndex = groups[groupIndex]->media.size()-1;
    }else{
        mediaIndex-=1;
    }
    groups[groupIndex]->media[mediaIndex]->play();

}
void MediaPlayer::draw(){
    if (que.size() > 0){
        ofDrawBitmapStringHighlight("loading gif: " +ofToString(queFileName) + "   "+ofToString(queIndex+1) + " / "+ofToString(que.size()), 20,20);
    }else{
        if (groups.size() > 0){
            
            if (groups[groupIndex]->media.size() >= mediaIndex+1){
                groups[groupIndex]->media[mediaIndex]->draw(frameOffsetX,frameOffsetY,frameWidth,frameHeight);
                if (drawUI == true){
                    ofDrawBitmapStringHighlight("File Name: "+ ofToString(groups[groupIndex]->media[mediaIndex]->getMoviePath()), 10,20);
                    ofDrawBitmapStringHighlight("Playback Position: "+ ofToString(groups[groupIndex]->media[mediaIndex]->getPosition())+" / 1.0", 10,40);
                    ofDrawBitmapStringHighlight("Group Name: "+  groups[groupIndex]->name + "  "+ofToString(groupIndex+1)+" / "+ofToString(groups.size()), 10,60);
                    ofDrawBitmapStringHighlight("index: "+ ofToString(mediaIndex+1)+" / "+ofToString(groups[groupIndex]->media.size()), 10,80);
                    if (loopingIndex <= 1){
                        ofDrawBitmapStringHighlight("LoopMode: none", 10,100);
                    
                    }else if (loopingIndex == 2){
                        ofDrawBitmapStringHighlight("LoopMode: loop", 10,100);
                    
                    }else{
                        ofDrawBitmapStringHighlight("LoopMode: ping-pong", 10,100);
                    }
                    ofDrawBitmapStringHighlight("StretchMode: "+ stretchMode, 10,120);
                }
            }
        }else{
            ofDrawBitmapStringHighlight("NO GIFS LOADED", boundWidth/2-100,boundHeight/2);
            ofDrawBitmapStringHighlight("drag and drop files, or a folder", boundWidth/2-170,boundHeight/2+40);
        }
    }
    if (drawUI == true){
        if (addingToGroup == true){
            ofDrawBitmapStringHighlight("GROUP MODE: ADD", boundWidth - 160,20);
        }else{
            ofDrawBitmapStringHighlight("GROUP MODE: CREATE", boundWidth - 160,20);
        }
        ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(),2), boundWidth - 160,60);
    }
}

void MediaPlayer::keyPressed(int key){
    cout << "key: "<<key<<"\n";
    if (key == 115){
        // s
        stretchIndex+= 1;
        if (stretchIndex > 2){
            stretchIndex = 0;
        }
        calculateDimensions();
    }
    
    if (key == 117){
        // u
        if (drawUI == true){
            drawUI = false;
        }else{
            drawUI = true;
        }
    }
    if (key == 2304){
        // shift
        if (addingToGroup == false){
            addingToGroup = true;
        }else{
            addingToGroup = false;
        }
    }
    if (queing == false){
    if (key == 357){
        //up
        resetMedia();
        if (groupIndex+1 >= groups.size()){
            groupIndex = 0;
        }else{
            groupIndex+=1;

        }
        groups[groupIndex]->media[mediaIndex]->play();

    }
    if (key == 359){
        // down
        resetMedia();
        if (groupIndex-1 < 0){
            groupIndex = groups.size()-1;
        }else{
            groupIndex-=1;
        }
        groups[groupIndex]->media[mediaIndex]->play();

    }
    if (key == 108){
        // l
        loopingIndex+=1;
    }
    if (key == 358){
        // right
        switchMedia(1);
    }
    if (key == 356){
        // left
        switchMedia(-1);
    }
    }
}
void MediaPlayer::keyReleased(int key){

}
void MediaPlayer::mousePressed(int x, int y, int button){
    
}
void MediaPlayer::mouseReleased(int x, int y, int button){
    
}