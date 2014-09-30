//
//  MediaGroup.h
//  GifMasher
//
//  Created by matthew radford on 9/28/14.
//
//


#include "Application.h"
#include <iostream>

#ifndef __GifMasher__MediaGroup__
#define __GifMasher__MediaGroup__

class MediaGroup{
public:
    int identity;
    string name;
    vector<ofVideoPlayer *> media;
    vector<string> exclude;
    
    void addMedia(ofVideoPlayer& player);
    void addExclude(string name);
    void flushExclude();
    Boolean isExcluded(string name);
    
    void update();
    void draw();
    
    MediaGroup(int identity,string name);

};
#endif /* defined(__GifMasher__MediaGroup__) */
