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


class GameScene : public CCScene {
public:
    GameScene();
    ~GameScene();
    static GameScene *create();
    bool init();
    
    GameLayer *control_layer;
    
    
    CCSprite *man;
    
};


GameScene *get_game_scene();


#endif /* defined(__ld27__GameScene__) */
