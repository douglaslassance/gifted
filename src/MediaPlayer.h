//
//  mediaPlayer.h
//  GifMasher
//
//  Created by matthew radford on 9/21/14.
//
//

#include "Application.h"

#ifndef _MediaPlayer
#define _MediaPlayer

class MediaPlayer{
    
public:
    void loadGifs(string path);
    void loadGif(string name);
    void loadFromQue(int index);
    void update();
    void draw();
    void calculateDimensions();
    void updateBounds();
    void switchMedia();
    void resetQue();
    void flushQue();
    void quefinished();
    void dropped(ofDragInfo dragInfo);
    void keyPressed(int key);
    void mouseMoved(int x, int y);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    Boolean stretch;
    int mediaIndex;
    float timedelta;
    float frameOffsetX;
    float frameOffsetY;
    float frameHeight;
    float frameWidth;
    float boundWidth;
    float boundHeight;
    Boolean queing;
    int queIndex;
    string queFileName;
    vector<string> que;
    vector<ofVideoPlayer *> media;
    ofVideoPlayer player;
    MediaPlayer();
    
    
};

#endif
