//
//  LoadScene.cpp
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#include "LoadScene.h"


LoadScene::LoadScene() {
    
    
}

LoadScene::~LoadScene() {
    
    
}

LoadScene *LoadScene::create() {
    LoadScene *r = new LoadScene();
    if ( r==NULL ) return NULL;
    if ( r->init() == false ) {
        delete r;
        return NULL;
    } else {
        r->autorelease();
    }
    return r;
}



bool LoadScene::init() {
    CCLabelTTF *t1;
    t1=CCLabelTTF::create("Loading... \nand doing complicated developer stuff..", "Marker Felt", 40);
    t1->setPosition(ccp(480,320));
    this->addChild(t1);

    loadAssets();
    
    this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(0.3), CCCallFunc::create(this,callfunc_selector(LoadScene::completed_load))));
    
    return true;
}




bool LoadScene::loadAssets() {
    printf("loading...\n");
    
    CCSpriteFrameCache *sf_cache;
    CCSpriteFrame *sf;
    sf_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    sf = CCSpriteFrame::create("prueba1_1.png", CCRectMake(0, 0, 64, 128))
    ;
    sf_cache->addSpriteFrame(sf, "correr_1");
    sf = CCSpriteFrame::create("prueba1_2.png", CCRectMake(0, 0, 64, 128))
    ;
    sf_cache->addSpriteFrame(sf, "correr_2");
    sf = CCSpriteFrame::create("prueba1_3.png", CCRectMake(0, 0, 64, 128))
    ;
    sf_cache->addSpriteFrame(sf, "correr_3");
    
    return true;
}


void LoadScene::completed_load() {
    printf("done\n");
    CCDirector::sharedDirector()->replaceScene(get_game_scene());
    
}

