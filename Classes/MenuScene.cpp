//
//  MenuScene.cpp
//  ld27
//
//  Created by Mikel on 25/08/13.
//
//

#include "MenuScene.h"

MenuScene *theMenuScene=NULL;


MenuScene::MenuScene() {
}

MenuScene::~MenuScene() {
}

MenuScene *MenuScene::create() {
    MenuScene *r = new MenuScene();
    if ( r==NULL ) return NULL;
    if ( r->init() == false ) {
        delete r;
        return NULL;
    } else {
        r->autorelease();
    }
    return r;
}


bool MenuScene::init() {
    startPanel=CCLayerColor::create((const ccColor4B){0,0,0,255});
    CCLabelTTF *t1;
    t1=CCLabelTTF::create("Last Ten Seconds", "Marker Felt", 40);
    t1->setPosition(ccp(480,500));
    startPanel->addChild(t1);
    CCMenuItemLabel *l1;
    l1=CCMenuItemLabel::create(CCLabelTTF::create("click to play", "Marker Felt", 40), this, menu_selector(action_play));
    CCMenu *m1=CCMenu::create(l1,NULL);
    startPanel->addChild(m1);
    
    
    
    return true;
}

static MenuScene *getMenuScene() {
    if (theMenuScene==NULL) {
        theMenuScene=MenuScene::create();
    }
    return theMenuScene;
}



void MenuScene::waitForPlay() {
    MenuScene *menu = MenuScene::getMenuScene();
    
    
    
}

void MenuScene::showWin() {
    MenuScene *menu = MenuScene::getMenuScene();
    
    
}

void MenuScene::showLost() {
    MenuScene *menu = MenuScene::getMenuScene();
    
    
}

void MenuScene::action_play() {
    printf("play\n");
}


