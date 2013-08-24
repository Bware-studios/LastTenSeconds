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

extern const float optimum_step_size;


class GameScene : public CCScene {
public:
    GameScene();
    ~GameScene();
    static GameScene *create();
    bool init();
    
    void unpaso(float paso);
    void start_explossion();
    
    
    CCAnimation *anim_run;
    class GameLayer *control_layer;
    static class GameScene *theGameScene;
    
    
    CCSpriteFrame *man_frames[8];
    CCSprite *man;
    float man_x;
    
    CCParticleExplosion *explossion1;
    CCParticleExplosion *explossion2;

};


GameScene *get_game_scene();


#endif /* defined(__ld27__GameScene__) */
