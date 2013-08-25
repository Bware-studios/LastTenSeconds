//
//  MenuScene.h
//  ld27
//
//  Created by Mikel on 25/08/13.
//
//

#ifndef __ld27__MenuScene__
#define __ld27__MenuScene__


#include "common.h"

#include "GameScene.h"



class MenuScene : public CCScene {
public:
    MenuScene();
    ~MenuScene();
    static MenuScene *create();
    bool init();
    
    static MenuScene *getMenuScene();
    
    static void waitForPlay();
    static void showWin();
    static void showLost();
    
    void action_play();
    
    
    CCLayerColor *startPanel;
    CCLayerColor *winPanel;
    CCLayerColor *lostPanel;
    
    
    
};

#endif /* defined(__ld27__MenuScene__) */
