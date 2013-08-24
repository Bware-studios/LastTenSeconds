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
    
    char running_name[]="running.png";
    int sw=128;
    int sh=256;
    sf_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    sf = CCSpriteFrame::create(running_name, CCRectMake(0*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run1");
    sf = CCSpriteFrame::create(running_name, CCRectMake(1*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run2");
    sf = CCSpriteFrame::create(running_name, CCRectMake(2*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run3");
    sf = CCSpriteFrame::create(running_name, CCRectMake(3*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run4");
    sf = CCSpriteFrame::create(running_name, CCRectMake(4*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run5");
    sf = CCSpriteFrame::create(running_name, CCRectMake(5*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run6");
    sf = CCSpriteFrame::create(running_name, CCRectMake(6*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run7");
    sf = CCSpriteFrame::create(running_name, CCRectMake(7*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run8");
    
    
    CCAnimationCache *an_cache;
    CCArray *frames;
    CCAnimation *anim;

    an_cache = CCAnimationCache::sharedAnimationCache();
    
    frames=CCArray::create(sf_cache->spriteFrameByName("run3"),sf_cache->spriteFrameByName("run4"),sf_cache->spriteFrameByName("run5"),sf_cache->spriteFrameByName("run6"),sf_cache->spriteFrameByName("run7"),sf_cache->spriteFrameByName("run8"),sf_cache->spriteFrameByName("run1"),sf_cache->spriteFrameByName("run2"),NULL);
    anim=CCAnimation::createWithSpriteFrames(frames,0.125);
    an_cache->addAnimation(anim, "run");
    
    return true;
}


void LoadScene::completed_load() {
    printf("done\n");
    CCDirector::sharedDirector()->replaceScene(get_game_scene());
    
}

