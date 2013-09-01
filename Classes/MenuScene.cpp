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

   
    
    currentPanel=NULL;
    
    return true;
}

MenuScene *MenuScene::getMenuScene() {
    if (theMenuScene==NULL) {
        theMenuScene=MenuScene::create();
    }
    return theMenuScene;
}



void MenuScene::waitForPlay() {
    
    startPanel=CCLayerColor::create((const ccColor4B){100,100,100,255});
    CCLabelTTF *t1;
    CCPoint tpos=center_position;
    tpos.y*=1.8;
    t1=CCLabelTTF::create("Last Ten Seconds", "Marker Felt", 70);
    t1->setPosition(tpos);
    t1->setColor((const ccColor3B){255,0,0});
    startPanel->addChild(t1);

    t1=CCLabelTTF::create("A simple 10-seconds game\nby Bware studios\nfor Ludum Dare LD#27", "Marker Felt", 40);
    tpos.y=center_position.y*1.2;
    t1->setPosition(tpos);
    t1->setColor((const ccColor3B){255,255,255});
    startPanel->addChild(t1);

    
    CCMenuItemLabel *l1;
    l1=CCMenuItemLabel::create(CCLabelTTF::create("click to play", "Marker Felt", 40), this, menu_selector(MenuScene::action_play));
    l1->setColor((const ccColor3B){0,0,255});
    CCMenu *m1=CCMenu::create(l1,NULL);
    tpos=center_position;
    tpos.y*=0.5;
    m1->setPosition(tpos);
    startPanel->addChild(m1);

    if (currentPanel) {
        //currentPanel->retain();
        removeChild(currentPanel);
    }
    currentPanel=startPanel;
    addChild(currentPanel);

    
    CCDirector::sharedDirector()->replaceScene(this);
}

void MenuScene::inGame() {
    sound_play_alarm();
    
    ingamePanel=CCLayerColor::create((const ccColor4B){100,100,100,255});
    CCLabelTTF *t1;
    CCPoint tpos=center_position;
    tpos.x*=1.3;
    
    t1=CCLabelTTF::create("A BOMB !!!\n There is a BOMB\nIt's about to explode", "Marker Felt", 40);
    tpos.y=center_position.y*1.7;
    t1->setPosition(tpos);
    t1->setColor((const ccColor3B){255,255,255});
    ingamePanel->addChild(t1);
    
    
    CCSprite *im1=CCSprite::create("inicio.png");
    CCPoint ipos;
    ipos=center_position;
    ipos.x*=0.5;
    im1->setPosition(ipos);
    ingamePanel->addChild(im1,5);
    

    t1=CCLabelTTF::create("The countdown is running\n while you think...\n10 seconds to go...", "Marker Felt", 40);
    tpos.y=center_position.y*0.7;
    t1->setPosition(tpos);
    t1->setColor((const ccColor3B){255,255,255});
    ingamePanel->addChild(t1);

    
    
    CCMenuItemLabel *l1;
    l1=CCMenuItemLabel::create(CCLabelTTF::create("go and deactivate it !!", "Marker Felt", 40), this, menu_selector(MenuScene::action_entergamescene));
    l1->setColor((const ccColor3B){0,0,255});
    CCMenu *m1=CCMenu::create(l1,NULL);
    tpos=center_position;
    tpos.x*=1.3;
    tpos.y*=0.2;
    m1->setPosition(tpos);
    ingamePanel->addChild(m1);
    
    if (currentPanel) {
        //currentPanel->retain();
        removeChild(currentPanel);
    }
    currentPanel=ingamePanel;
    addChild(currentPanel);
    
    
    //CCDirector::sharedDirector()->replaceScene(this);
}



void MenuScene::showWin() {
    char smsg[300];
    winPanel=CCLayerColor::create((const ccColor4B){100,100,100,255});
    CCSprite *im1=CCSprite::create("final.png");
    CCPoint ipos=center_position;
    ipos.x/=2.0;
    im1->setPosition(ipos);
    winPanel->addChild(im1);
    sprintf(smsg, "You are a hero!!!\n%.1f seconds left\nShare/tweet this...\ntake the photo yourself\nwe had no time to finish...",get_game_scene()->score_seconds_left);
    CCLabelTTF *t1=CCLabelTTF::create(smsg, "Marker Felt", 40);
    ipos=center_position;
    ipos.y*=1.2;
    ipos.x*=1.5;
    t1->setPosition(ipos);
    winPanel->addChild(t1);
    CCMenuItemLabel *l1=CCMenuItemLabel::create(CCLabelTTF::create("try again", "Marker Felt", 40), this, menu_selector(MenuScene::waitForPlay));
    l1->setColor((const ccColor3B){0,0,255});

    CCMenu *m1=CCMenu::create(l1,NULL);
    ipos=center_position;
    ipos.y*=0.5;
    ipos.x*=1.5;
    m1->setPosition(ipos);
    winPanel->addChild(m1);
    
    if (currentPanel) {
        //currentPanel->retain();
        removeChild(currentPanel);
    }
    currentPanel=winPanel;
    addChild(currentPanel);
    
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void MenuScene::showLost() {
    CCPoint ipos;
    
    lostPanel=CCLayerColor::create((const ccColor4B){100,100,100,255});
    CCLabelTTF *t1=CCLabelTTF::create("You nearly got it...\nBut there is no silver medal\nfor a bomb deactivator", "Marker Felt", 40);
    ipos=center_position;
    ipos.x*=1.5;
    ipos.y*=1.6;
    t1->setPosition(ipos);
    lostPanel->addChild(t1);
    CCMenuItemLabel *l1=CCMenuItemLabel::create(CCLabelTTF::create("try again", "Marker Felt", 40), this, menu_selector(MenuScene::waitForPlay));
    l1->setColor((const ccColor3B){0,0,255});
    
    CCSprite *im1=CCSprite::create("final2.png");
    ipos=center_position;
    ipos.x*=0.5;
    ipos.y*=1.3;
    im1->setPosition(ipos);
    lostPanel->addChild(im1,5);

    CCMenu *m1=CCMenu::create(l1,NULL);
    ipos=center_position;
    ipos.x*=1.5;
    ipos.y*=0.7;
    m1->setPosition(ipos);
    lostPanel->addChild(m1);

    if (currentPanel) {
        //currentPanel->retain();
        removeChild(currentPanel);
    }
    currentPanel=lostPanel;
    addChild(currentPanel);

    
    CCDirector::sharedDirector()->replaceScene(this);
}

void MenuScene::action_play() {
    inGame();
}

void MenuScene::action_entergamescene() {
    sound_stop_alarm();
    this->retain();
    CCDirector::sharedDirector()->replaceScene(get_game_scene());
}


