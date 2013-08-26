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
    void runinput_stepInputEnded();
    
    float tnow;
    CCLabelTTF *countdown_counterT;

    
    
    bool jump_enabled;
    bool reachedbomb_enabled;
    bool explosion_enabled;
    bool beginning;
    
    CCLabelTTF *runinput_valueT;
    
    
    bool on_step;
    float runinput_lastStepTime;

    bool runinput_step;
    bool first_step;
    bool runinput_enabled;
    bool runinput_down;
    bool runinput_stepdone;
    float runinput_alfaBar;
    float runinput_down_time;
    
    float paso;
    
};

#endif /* defined(__ld27__GameLayer__) */
