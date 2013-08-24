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

class GameLayer : public CCLayer {
public:
    GameLayer();
    ~GameLayer();
    static GameLayer *create();
    bool init();
    
    
    
};

#endif /* defined(__ld27__GameLayer__) */
