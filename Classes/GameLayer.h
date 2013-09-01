//
//  GameLayer.h
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#ifndef __ld27__GameLayer__
#define __ld27__GameLayer__

#include <stdio.h>
#include "common.h"
#include "GameScene.h"


extern const bool show_debug_info;


extern const float step_time;
extern const float slowmotion_factor;



class GameLayer : public CCLayer {
public:
    GameLayer();
    ~GameLayer();
    static GameLayer *create();
    bool init();
    
    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    void ccTouchMoved(CCTouch *touch, CCEvent *event);
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
    void ccTouchCancelled(CCTouch *touch, CCEvent *event);

    void update(float dt);
    void draw();
    
    void runinput_enable();
    void runinput_tryNewStep();

    void recover_from_fall();
    void deactivated();
    void exploded();
    
    float tnow;
    float tgame;
    float current_slowmotion_factor;
    CCLabelTTF *countdown_counterT;

    // to start explossion once
    bool explossion_started;

    bool runinput_enabled;

    // if a step has been input and has a length
    // may be waitng to the previous to finish
    bool runinput_step_inputready;
    float runinput_stepx;
    bool runinput_onstep_anim;
    float runinput_currentstep_finish_time;

    // button flag to press just once
    bool runinput_down;

    // for debug
    CCLabelTTF *runinput_valueT;

    
    bool jump_enabled;
    bool reachedbomb_enabled;
    bool beginning;
    
    bool bomb_deactivated;
    bool bomb_exploded;
    
    bool on_step;
    float runinput_lastStepTime;

    //bool runinput_step;
    bool first_step;
    bool runinput_stepdone;
    float runinput_alfaBar;
 //   float runinput_down_time;
    
    float paso;
    
};

#endif /* defined(__ld27__GameLayer__) */
