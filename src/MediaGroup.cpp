//
//  MediaGroup.cpp
//  GifMasher
//
//  Created by matthew radford on 9/28/14.
//
//

#include "MediaGroup.h"

MediaGroup::MediaGroup(int idNum,string idName){
    name = idName;
    identity = idNum;
    cout << "constructed media group with name: " << name << "\n";
    
}

void MediaGroup::addMedia(ofVideoPlayer& player){
    media.push_back(&player);
}

Boolean MediaGroup::isExcluded(string name){
    if (ofContains(exclude,name) == true){
        return true;
    }else{
        return false;
    }
}
void MediaGroup::addExclude(string name){
    if (ofContains(exclude, name) == false){
        exclude.push_back(name);
    }
}

void MediaGroup::flushExclude(){
    exclude.clear();
}

void MediaGroup::update(){
    
}

void MediaGroup::draw(){
    
}