//
//  GameScene.cpp
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#include "GameScene.h"


GameScene *theGameScene=NULL;

GameScene::GameScene() {
    
}

GameScene::~GameScene() {
    
}

GameScene *GameScene::create() {
    GameScene *r = new GameScene();
    if ( r==NULL ) return NULL;
    if ( r->init() == false ) {
        delete r;
        return NULL;
    } else {
        r->autorelease();
    }
    return r;
}

bool GameScene::init() {
    
    CCLayerColor *background;
    background=CCLayerColor::create((const ccColor4B){200,200,200,255});
    this->addChild(background,0);
    
    CCLayerColor *suelo;
    suelo=CCLayerColor::create((const ccColor4B){0,100,0,255}, 1000, 100);
    suelo->ignoreAnchorPointForPosition(false);
    suelo->setAnchorPoint(ccp(0.5,0.5));
    suelo->setPosition(ccp(480,200));
    this->addChild(suelo,10);
    
    control_layer=GameLayer::create();
    this->addChild(control_layer,200);
    
    man=CCSprite::createWithSpriteFrameName("correr_1");
    man->setAnchorPoint(ccp(0.5,0));
    man->setPosition(ccp(10,200));
    this->addChild(man,20);
    
    return true;
}



GameScene *get_game_scene() {
    if (theGameScene==NULL) {
        theGameScene=GameScene::create();
    }
    
    return theGameScene;
}
