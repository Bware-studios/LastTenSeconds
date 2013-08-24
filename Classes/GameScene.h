//
//  GameScene.h
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#ifndef __ld27__GameScene__
#define __ld27__GameScene__


#include "common.h"
#include "GameLayer.h"

;


class GameScene : public CCScene {
public:
    GameScene();
    ~GameScene();
    static GameScene *create();
    bool init();
    
    void unpaso(int paso);
    
    
    class GameLayer *control_layer;
    static class GameScene *theGameScene;
    
    
    CCSpriteFrame *man_frames[3];
    CCSprite *man;
    float man_x;
};


GameScene *get_game_scene();


#endif /* defined(__ld27__GameScene__) */
