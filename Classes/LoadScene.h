//
//  LoadScene.h
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#ifndef __ld27__LoadScene__
#define __ld27__LoadScene__

#include "common.h"

#include "GameScene.h"
#include "MenuScene.h"



class LoadScene : public CCScene {
public:
    LoadScene();
    ~LoadScene();
    static LoadScene *create();
    bool init();
    
    bool loadAssets();
    
    void completed_load();
    
};


#endif /* defined(__ld27__LoadScene__) */
