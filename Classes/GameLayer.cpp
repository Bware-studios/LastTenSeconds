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
    
    
    return true;
}


