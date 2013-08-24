//
//  GameScene.cpp
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#include "GameScene.h"

const float optimum_step_size = 100.0;


GameScene *GameScene::theGameScene=NULL;

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
    anim_run=CCAnimationCache::sharedAnimationCache()->animationByName("run");

    
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
    
    explossion1=CCParticleExplosion::createWithTotalParticles(100);
    explossion2=CCParticleExplosion::createWithTotalParticles(100);
    explossion1->stopSystem();
    explossion2->stopSystem();
    explossion1->setStartSize(100);
    explossion1->setStartSizeVar(50);
    explossion2->setStartSize(70);
    explossion2->setStartSizeVar(30);
    //explossion->setEndSize(300);
    //explossion->setEndSizeVar(50);
    //explossion->setStartSpin(0);
    //explossion->setStartSpinVar(180);
    //explossion->setEndSpin(0);
    //explossion->setEndSpinVar(180);
    explossion1->setSpeed(500);
    explossion1->setSpeedVar(300);
    explossion2->setSpeed(800);
    explossion2->setSpeedVar(200);
    explossion1->setStartColor((const ccColor4F){1.0,0.4,0.0,1.0});
    explossion1->setStartColorVar((const ccColor4F){.1,.1,0,.3});
    explossion1->setEndColor((const ccColor4F){1.0,0.4,0.0,1.0});
    explossion1->setEndColorVar((const ccColor4F){.1,.1,0,.3});
    explossion2->setStartColor((const ccColor4F){.8,0.8,0.0,1.0});
    explossion2->setStartColorVar((const ccColor4F){.1,.1,0,.3});
    explossion1->setAngle(90);
    explossion1->setAngleVar(90);
    explossion2->setAngle(90);
    explossion2->setAngleVar(90);
    explossion1->setLife(1.0);
    explossion1->setLifeVar(0.2);
    explossion2->setLife(.5);
    explossion2->setLifeVar(0.1);

    addChild(explossion1,20);
    addChild(explossion2,22);

    
    explossion1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("run1"));
    
    man_frames[0]=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run1");
    man_frames[1]=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run2");
    man_frames[2]=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run3");
    man_frames[3]=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run4");
    man_frames[4]=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run5");
    man_frames[5]=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run6");
    man_frames[6]=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run7");
    man_frames[7]=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run8");

    
    man_x=0;
    man=CCSprite::createWithSpriteFrameName("run1");
    man->setAnchorPoint(ccp(0.5,0));
    man->setPosition(ccp(10+man_x,200));
    //man->runAction(CCRepeatForever::create(CCAnimate::create(anim_run)));
    
    unpaso(optimum_step_size);

    this->addChild(man,20);

    
    return true;
}


void GameScene::unpaso(float paso) {
//    man_x+=5;
//    man->setPosition(ccp(10+man_x,200));
//    man->setDisplayFrame(man_frames[paso%8]);
    man->runAction(CCAnimate::create(anim_run));
    man->runAction(CCMoveBy::create(1.0, ccp(paso,0)));

}


void GameScene::start_explossion() {
    printf("booom\n");
    explossion1->setPosition(ccp(800,220));
    explossion1->resetSystem();
    explossion2->setPosition(ccp(800,220));
    explossion2->resetSystem();
}

GameScene *get_game_scene() {
    if (GameScene::theGameScene==NULL) {
        GameScene::theGameScene=GameScene::create();
    }
    
    return GameScene::theGameScene;
}
