//
//  GameScene.cpp
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#include "GameScene.h"

const float optimum_step_size = 100.0;
const int num_objetos = 4;
const int num_people = 3;
const float baseline_height = 100.0;
const CCPoint bomb_position=ccp(800,baseline_height+25);
const CCPoint center_position=ccp(480,320);


// velocity for object at 100px
const float explossion_object_velocityk = 1000.0;
const float explossion_object_avelocity = 90.0;
const float explossion_object_time = 3.0;

GameScene *GameScene::theGameScene=NULL;

GameScene::GameScene() {
    
}

GameScene::~GameScene() {
    theGameScene=NULL;
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
    anim_run=new CCAnimation*[2];
    
    anim_run[0]=CCAnimationCache::sharedAnimationCache()->animationByName("run_step1");
    anim_run[1]=CCAnimationCache::sharedAnimationCache()->animationByName("run_step2");
    
    anim_fall=CCAnimationCache::sharedAnimationCache()->animationByName("fall");

    
    istep=0;

    
    CCLayerColor *background;
    background=CCLayerColor::create((const ccColor4B){0,0,0,255});
    this->addChild(background,0);
    
    CCSprite *background_wall;
    background_wall=CCSprite::create("fondo.png");
    background_wall->setAnchorPoint(ccp(0.5,0));
    background_wall->setPosition(ccp(center_position.x,baseline_height));
    addChild(background_wall,1);
    
//    CCLayerColor *suelo;
//    suelo=CCLayerColor::create((const ccColor4B){0,100,0,255}, 1000, 100);
//    suelo->ignoreAnchorPointForPosition(false);
//    suelo->setAnchorPoint(ccp(0.5,0.5));
//    suelo->setPosition(ccp(480,200));
//    this->addChild(suelo,10);
    
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
    explossion2->setEndColor((const ccColor4F){.8,0.8,0.0,1.0});
    explossion2->setEndColorVar((const ccColor4F){.1,.1,0,.3});
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

    
    //explossion1->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()-> spriteFrameByName("run1"));


    objetos=new CCSprite*[num_objetos];

    objetos[0]=CCSprite::createWithSpriteFrameName("bomb");
    objetos[0]->setPosition(bomb_position);
    objetos[0]->setAnchorPoint(ccp(0.5,0));
    addChild(objetos[0],15);
    
    int i;
    char oname[]="obj1";
    for (i=1;i<num_objetos;i++) {
        sprintf(oname,"obj%u",(int)(1+(random()%6)));
        objetos[i]=CCSprite::createWithSpriteFrameName(oname);
        objetos[i]->setAnchorPoint(ccp(0.5,0));
        objetos[i]->setPosition(ccp(200*i+r_unif(0,100),baseline_height+85));
        addChild(objetos[i],12);
    }
    
    people=new CCSprite*[num_people];

    
    char pname[]="people1_1";
    for (i=0;i<num_people;i++) {
        int j;
        j=(int)(1+(random()%3));
        j=1+(i%3);
        sprintf(pname,"people%u_1",j);
        people[i]=CCSprite::createWithSpriteFrameName(pname);
        people[i]->setAnchorPoint(ccp(0.5,0));
        people[i]->setPosition(ccp(200+220*i+r_unif(0,100),baseline_height+60));
        people[i]->setFlipX(CCRANDOM_0_1()>0.5);
        addChild(people[i],14);
//        sprintf(pname,"people%u",j);
//        people[i]->runAction(CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(pname))));
    }
    
    
    
    man_x=0;
    man=CCSprite::createWithSpriteFrameName("run3");
    man->setAnchorPoint(ccp(0.5,0));
    man->setPosition(ccp(40,baseline_height+20));
    //man->runAction(CCRepeatForever::create(CCAnimate::create(anim_run)));


    
    //unpaso(optimum_step_size);
    sound_play_slowmotionsong();
    this->addChild(man,20);

    
    return true;
}


void GameScene::unpaso(float paso) {
//    man_x+=5;
//    man->setPosition(ccp(10+man_x,200));
//    man->setDisplayFrame(man_frames[paso%8]);
    
    man->runAction(CCAnimate::create(anim_run[istep%2]));
    man->runAction(CCMoveBy::create(step_time, ccp(paso,0)));

    istep+=1;
}

void GameScene::fall() {
    man->setAnchorPoint(ccp(0.25,0));
    man->runAction(CCAnimate::create(anim_fall));
}



void GameScene::check_win() {
    CCPoint manpos=man->getPosition();
    if (fabs(manpos.x-bomb_position.x) < 5.0) {
        score_seconds_left=10-control_layer->tnow;
        schedule_win();
    }
}


void GameScene::start_explossion() {
    printf("booom\n");
    explossion1->setPosition(bomb_position);
    explossion1->resetSystem();
    explossion2->setPosition(bomb_position);
    explossion2->resetSystem();
    
    int i;
    for (i=1;i<num_objetos;i++) {
        explossion_move_sprite(objetos[i]);
    }
    for (i=0;i<num_people;i++) {
        explossion_move_sprite(people[i]);
    }
    explossion_move_sprite(man);
    removeChild(objetos[0]);
    
    sound_stop_slowmotionsong();
    sound_play_effect(sound_explosion_name);
    
    runAction(CCSequence::create(CCDelayTime::create(3.0),CCCallFunc::create(this, callfunc_selector(GameScene::schedule_lost)),NULL));
}

void GameScene::explossion_move_sprite(CCSprite *s) {
    CCPoint spos=s->getPosition();
    CCPoint v;
    float d;
    float av;
    v.x=spos.x-bomb_position.x;
    v.y=spos.y-bomb_position.y;
    d=sqrtf(v.x*v.x+v.y*v.y);
    v.x/=d;
    v.y/=d;
    av=v.x*explossion_object_avelocity;
    v.x*=explossion_object_velocityk*100.0/d;
    v.y*=explossion_object_velocityk*100.0/d;
    v.x*=explossion_object_time;
    v.y*=explossion_object_time;
    s->stopAllActions();
    s->runAction(CCMoveBy::create(explossion_object_time,v));
    s->runAction(CCRotateBy::create(explossion_object_time, av*explossion_object_time));
}





void GameScene::schedule_win() {
    sound_stop_slowmotionsong();
    MenuScene::getMenuScene()->showWin();
}

void GameScene::schedule_lost() {
    sound_stop_slowmotionsong();
    MenuScene::getMenuScene()->showLost();
}


GameScene *get_game_scene() {
    if (GameScene::theGameScene==NULL) {
        GameScene::theGameScene=GameScene::create();
    }
    
    return GameScene::theGameScene;
}





