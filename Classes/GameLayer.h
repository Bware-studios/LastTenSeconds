//
//  GameLayer.h
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#ifndef __ld27__GameLayer__
#define __ld27__GameLayer__


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

    
    
    int paso;
    
};

#endif /* defined(__ld27__GameLayer__) */
