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
    void runinput_doStep();
    
    float tnow;
    CCLabelTTF *countdown_counterT;

    
    
    bool jump_enabled;
    bool reachedbomb_enabled;
    bool explosion_enabled;
    
    bool runinput_enabled;
    float runinput_lastStepTime;
    float runinput_alfaBar;
    float runinput_downalfa;
    bool runinput_down;
    float runinput_upalfa;
    bool runinput_up;
    CCLabelTTF *runinput_valueT;
    
    int paso;
    
};

#endif /* defined(__ld27__GameLayer__) */
