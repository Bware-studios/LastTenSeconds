//
//  GameScene.cpp
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#include "GameScene.h"

const float optimum_step_size = 30.0;
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
    anim_jump=CCAnimationCache::sharedAnimationCache()->animationByName("jump");

    
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
    
    deactivate_dialog=NULL;
    
    
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


void GameScene::step(float stepdistance) {
//    man_x+=5;
//    man->setPosition(ccp(10+man_x,200));
//    man->setDisplayFrame(man_frames[paso%8]);
    
    man->runAction(CCAnimate::create(anim_run[istep%2]));
    man->runAction(CCMoveBy::create(step_time, ccp(stepdistance,0)));

    istep+=1;
}


void GameScene::jump() {
    man->setAnchorPoint(ccp(0.25,0));
    man->runAction(CCSequence::create(CCAnimate::create(anim_jump),CCMoveBy::create(0.6, ccp(200,-30)),CCCallFunc::create(this,callfunc_selector(GameScene::schedule_jumpend)),NULL));
    
}

void GameScene::fall() {
    man->setAnchorPoint(ccp(0.25,0));
    man->runAction(CCSequence::create(CCAnimate::create(anim_fall),CCCallFunc::create(this,callfunc_selector(GameScene::schedule_fallend)),NULL));
}

void GameScene::start_deactivation() {
    CCPoint pos;
    pos=man->getPosition();
    man->setPosition(ccp(pos.x,baseline_height+20));
    man->stopAllActions();
    man->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("deactivating"));
    control_layer->runinput_enabled=false;
    control_layer->runinput_down=false;
    
    show_deactivation();

    
}


void GameScene::check_reachbomb() {
    CCPoint manpos=man->getPosition();
    if (fabs(manpos.x-bomb_position.x) < 5.0) {
        start_deactivation();
        score_seconds_left=10-control_layer->tgame;
       // schedule_win();
    }
}


void GameScene::start_explossion() {
    //printf("booom\n");
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
    
    if (deactivate_dialog) { explossion_move_sprite(deactivate_dialog); }
    
    removeChild(objetos[0]);
    
    sound_stop_slowmotionsong();
    sound_play_effect(sound_explosion_name);
    
    runAction(CCSequence::create(CCDelayTime::create(3.0),CCCallFunc::create(this, callfunc_selector(GameScene::schedule_lost)),NULL));
    
    control_layer->exploded();
}

void GameScene::explossion_move_sprite(CCNode *s) {
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



void GameScene::show_deactivation() {
    float dwr,dhr;
    if (deactivate_dialog) return;
    
    dwr=250;
    dhr=200;
    
    deactivate_dialog=CCLayerColor::create((const ccColor4B){150,180,150,220}, 2*dwr, 2*dhr);
    deactivate_dialog->setAnchorPoint(ccp(0.5,0.5));
    deactivate_dialog->ignoreAnchorPointForPosition(false);
    deactivate_dialog->setPosition(center_position);
    CCSprite *im=CCSprite::createWithSpriteFrameName("bomb");
    im->setAnchorPoint(ccp(0.5,0));
    im->setPosition(ccp(dwr,dhr+50));
    deactivate_dialog->addChild(im);
    CCLabelTTF *l1;
    l1=CCLabelTTF::create("Which cable will you cut??", "Marker Felt", 40);
    l1->setPosition(ccp(dwr,dhr));
    deactivate_dialog->addChild(l1);
    
    const char *mtexts[3]={"red","green","blue"};
    ccColor3B mcolors[3]={(const ccColor3B){255,0,0},(const ccColor3B){0,255,0},(const ccColor3B){0,0,255}};
    CCMenuItemLabel *ml1[3];
    SEL_MenuHandler mls1[3]={menu_selector(GameScene::cut_bad_wire),menu_selector(GameScene::cut_bad_wire),menu_selector(GameScene::cut_bad_wire)};
    int i;

    i=((int)(CCRANDOM_0_1()*1000))%3;
    mls1[i]=menu_selector(GameScene::cut_good_wire);
    // hint
    //mcolors[i]=(const ccColor3B){255,255,255};
    
    for (i=0;i<3;i++) {
        ml1[i]=CCMenuItemLabel::create(CCLabelTTF::create(mtexts[i], "Marker Felt", 40), this, mls1[i]);
        ml1[i]->setColor(mcolors[i]);
        ml1[i]->setPosition(ccp(-100+i*100,0));
    }
    CCMenu *m1;
    m1=CCMenu::create(ml1[0],ml1[1],ml1[2],NULL);
    m1->setPosition(ccp(dwr,dhr-100));
    deactivate_dialog->addChild(m1);
    
    addChild(deactivate_dialog,50);
}

void GameScene::cut_bad_wire() {
    start_explossion();
}

void GameScene::cut_good_wire() {
    control_layer->deactivated();
    win_anim_start();
}


void GameScene::win_anim_start() {
    sound_stop_slowmotionsong();
    removeChild(deactivate_dialog);
    win_loop_i=5;
    win_anim_loop();
}

void GameScene::win_anim_loop() {
    if (win_loop_i==0) {
        schedule_win();
        return;
    }
    man->runAction(CCSequence::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("celebrating")),CCCallFunc::create(this,callfunc_selector(GameScene::win_anim_loop)),NULL));
    
    //CCSequence *jump_seq=CCSequence::create(CCMoveBy::create(0.3, ccp(0,40)),CCMoveBy::create(0.3,ccp(0,-40)),NULL);
    int i;
    for (i=0;i<num_people;i++) {
        people[i]->runAction(CCSequence::create(CCDelayTime::create(0.2*CCRANDOM_0_1()),CCMoveBy::create(0.25, ccp(0,40)),CCMoveBy::create(0.25,ccp(0,-40)),NULL));
    }
    win_loop_i-=1;
}

void GameScene::schedule_jumpend() {
    CCPoint pos;
    pos=man->getPosition();
    man->setPosition(ccp(pos.x,pos.y+30));
    man->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("down"));
}

void GameScene::schedule_fallend() {
    man->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("run3"));
    man->setAnchorPoint(ccp(0.5,0));
    control_layer->recover_from_fall();
}

void GameScene::schedule_win() {
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





