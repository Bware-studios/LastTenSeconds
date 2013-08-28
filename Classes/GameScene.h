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

extern const float baseline_height;
extern const CCPoint center_position;

extern const float optimum_step_size;


class GameScene : public CCScene {
public:
    GameScene();
    ~GameScene();
    static GameScene *create();
    bool init();
    
    void step(float stepdistance);
    void fall();
    void check_win();
    void start_explossion();
    void explossion_move_sprite(CCSprite *s);

    void schedule_win();
    void schedule_lost();

    CCAnimation *anim_fall;
    CCAnimation **anim_run;
    int istep;
    class GameLayer *control_layer;
    static class GameScene *theGameScene;
    
    
    CCSprite **objetos;
    CCSprite **people;
    
    CCSprite *man;
    float man_x;
    
    float score_seconds_left;
    
    CCParticleExplosion *explossion1;
    CCParticleExplosion *explossion2;

};


GameScene *get_game_scene();


#endif /* defined(__ld27__GameScene__) */
