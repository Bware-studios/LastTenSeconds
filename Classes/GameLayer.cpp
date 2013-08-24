//
//  GameLayer.cpp
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#include "GameLayer.h"

GameLayer::GameLayer() {
}

GameLayer::~GameLayer() {
}

GameLayer *GameLayer::create() {
    GameLayer *r = new GameLayer();
    if ( r==NULL ) return NULL;
    if ( r->init() == false ) {
        delete r;
        return NULL;
    } else {
        r->autorelease();
    }
    return r;
}

bool GameLayer::init() {
    
    printf("control layer created\n");
    
    //this->setKeypadEnabled(true);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    paso=0;
    
    return true;
}


bool GameLayer::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    printf("touch\n");
    paso+=1;
    GameScene::theGameScene->unpaso(paso);
    
    return true;
}

void GameLayer::ccTouchMoved(CCTouch *touch, CCEvent *event) {
    
}

void GameLayer::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    
}

void GameLayer::ccTouchCancelled(CCTouch *touch, CCEvent *event) {
    
}
