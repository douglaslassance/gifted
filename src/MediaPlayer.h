//
//  mediaPlayer.h
//  GifMasher
//
//  Created by matthew radford on 9/21/14.
//
//

#include "Application.h"
#include "MediaGroup.h"
# define OF_KEY_SHIFT 0x0400

#ifndef _MediaPlayer
#define _MediaPlayer

class MediaPlayer{
    
public:
    void loadGifs(string path,MediaGroup* group);
    void loadSingleGif(string path,MediaGroup* group);
    void loadGif(string name);
    void loadFromQue(int index);
    void update();
    void draw();
    void calculateDimensions();
    void updateBounds();
    void switchMedia(int amt);
    void resetQue();
    void flushQue();
    void quefinished();
    void dropped(ofDragInfo dragInfo);
    void keyPressed(int key);
    void keyReleased(int key);
    void resetMedia();
    void mouseMoved(int x, int y);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void makeGroup(string name);
    void manageLooping();
    void changeMediaForwards();
    void changeMediaBackwards();
    void shuffleMedia();
    void shuffleFrame();
    MediaGroup findGroup(string name);
    
    string stretchMode;
    int mediaIndex;
    int stretchIndex;
    int loopingIndex;
    int lastLoopingIndex;
    float timedelta;
    float frameOffsetX;
    float frameOffsetY;
    float frameHeight;
    float frameWidth;
    float boundWidth;
    float boundHeight;
    Boolean queing;
    Boolean addingToGroup;
    Boolean drawUI;
    int queIndex;
    int groupIndex;
    string queFileName;
    vector<MediaGroup *> groups;
    vector<string> que;
    ofVideoPlayer player;
    MediaPlayer();
    
    
};

#endif
