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
    

    sound_preload_all();
    
    CCSpriteFrameCache *sf_cache;
    CCSpriteFrame *sf;

    char *file_name;
    char running_name[]="running.png";
    file_name=running_name;
    int sw=128;
    int sh=256;
    sf_cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    sf = CCSpriteFrame::create(file_name, CCRectMake(0*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run1");
    sf = CCSpriteFrame::create(file_name, CCRectMake(1*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run2");
    sf = CCSpriteFrame::create(file_name, CCRectMake(2*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run3");
    sf = CCSpriteFrame::create(file_name, CCRectMake(3*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run4");
    sf = CCSpriteFrame::create(file_name, CCRectMake(4*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run5");
    sf = CCSpriteFrame::create(file_name, CCRectMake(5*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run6");
    sf = CCSpriteFrame::create(file_name, CCRectMake(6*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run7");
    sf = CCSpriteFrame::create(file_name, CCRectMake(7*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "run8");

    
    char muebles_name[]="muebles.png";
    file_name=muebles_name;
    sw=256;
    sh=256;
    sf = CCSpriteFrame::create(file_name, CCRectMake(0*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "bomb");
    sf = CCSpriteFrame::create(file_name, CCRectMake(1*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "obj1");
    sf = CCSpriteFrame::create(file_name, CCRectMake(2*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "obj2");
    sf = CCSpriteFrame::create(file_name, CCRectMake(3*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "obj3");
    sf = CCSpriteFrame::create(file_name, CCRectMake(4*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "obj4");
    sf = CCSpriteFrame::create(file_name, CCRectMake(5*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "obj5");
    sf = CCSpriteFrame::create(file_name, CCRectMake(6*sw, 0, sw, sh));
    sf_cache->addSpriteFrame(sf, "obj6");

    
    char people_name[]="testigos.png";
    file_name=people_name;
    sw=256;
    sh=256;
    sf = CCSpriteFrame::create(file_name, CCRectMake(0*sw, 0*sh, sw, sh));
    sf_cache->addSpriteFrame(sf, "people1_1");
//    sf = CCSpriteFrame::create(file_name, CCRectMake(1*sw, 0*sh, sw, sh));
//    sf_cache->addSpriteFrame(sf, "people1_2");
//    sf = CCSpriteFrame::create(file_name, CCRectMake(2*sw, 0*sh, sw, sh));
//    sf_cache->addSpriteFrame(sf, "people1_3");
    sf = CCSpriteFrame::create(file_name, CCRectMake(1*sw, 0*sh, sw, sh));
    sf_cache->addSpriteFrame(sf, "people2_1");
//    sf = CCSpriteFrame::create(file_name, CCRectMake(1*sw, 1*sh, sw, sh));
//    sf_cache->addSpriteFrame(sf, "people2_2");
//    sf = CCSpriteFrame::create(file_name, CCRectMake(2*sw, 1*sh, sw, sh));
//    sf_cache->addSpriteFrame(sf, "people2_3");
    sf = CCSpriteFrame::create(file_name, CCRectMake(2*sw, 0*sh, sw, sh));
    sf_cache->addSpriteFrame(sf, "people3_1");
//    sf = CCSpriteFrame::create(file_name, CCRectMake(1*sw, 2*sh, sw, sh));
//    sf_cache->addSpriteFrame(sf, "people3_2");
//    sf = CCSpriteFrame::create(file_name, CCRectMake(2*sw, 2*sh, sw, sh));
//    sf_cache->addSpriteFrame(sf, "people3_3");
    
    
    CCAnimationCache *an_cache;
    CCArray *frames;
    CCAnimation *anim;

    an_cache = CCAnimationCache::sharedAnimationCache();
    
    frames=CCArray::create(sf_cache->spriteFrameByName("run3"),sf_cache->spriteFrameByName("run4"),sf_cache->spriteFrameByName("run5"),sf_cache->spriteFrameByName("run6"),sf_cache->spriteFrameByName("run7"),sf_cache->spriteFrameByName("run8"),sf_cache->spriteFrameByName("run1"),sf_cache->spriteFrameByName("run2"),NULL);
    anim=CCAnimation::createWithSpriteFrames(frames,0.125/*/slowmotion_factor*/);
    an_cache->addAnimation(anim, "run");

//    frames=CCArray::create(sf_cache->spriteFrameByName("people1_1"),sf_cache->spriteFrameByName("people1_2"),sf_cache->spriteFrameByName("people1_3"),NULL);
//    anim=CCAnimation::createWithSpriteFrames(frames,1/slowmotion_factor);
//    an_cache->addAnimation(anim, "people1");
//
//    frames=CCArray::create(sf_cache->spriteFrameByName("people2_1"),sf_cache->spriteFrameByName("people2_2"),sf_cache->spriteFrameByName("people2_3"),NULL);
//    anim=CCAnimation::createWithSpriteFrames(frames,0.5/slowmotion_factor);
//    an_cache->addAnimation(anim, "people2");
//
//    frames=CCArray::create(sf_cache->spriteFrameByName("people3_1"),sf_cache->spriteFrameByName("people3_2"),sf_cache->spriteFrameByName("people3_3"),NULL);
//    anim=CCAnimation::createWithSpriteFrames(frames,0.7/slowmotion_factor);
//    an_cache->addAnimation(anim, "people3");

    
    
    
    return true;
}


void LoadScene::completed_load() {
    printf("done\n");
    //CCDirector::sharedDirector()->replaceScene(get_game_scene());
    MenuScene::getMenuScene()->waitForPlay();
}

