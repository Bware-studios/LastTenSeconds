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
    void jump();
    void fall();
    void start_deactivation();
    void check_reachbomb();
    void start_explossion();
    void explossion_move_sprite(CCNode *s);
    void show_deactivation();

    void cut_bad_wire();
    void cut_good_wire();
    
    void win_anim_start();
    void win_anim_loop();
    
    void schedule_jumpend();
    void schedule_fallend();
    void schedule_win();
    void schedule_lost();

    CCLayerColor *deactivate_dialog;
    
    CCAnimation *anim_fall;
    CCAnimation *anim_jump;
    CCAnimation **anim_run;
    int istep;
    class GameLayer *control_layer;
    static class GameScene *theGameScene;
    
    
    CCSprite **objetos;
    CCSprite **people;
    
    CCSprite *man;
    float man_x;
    
    float score_seconds_left;
    
    int win_loop_i;
    
    
    CCParticleExplosion *explossion1;
    CCParticleExplosion *explossion2;

};


GameScene *get_game_scene();


#endif /* defined(__ld27__GameScene__) */
