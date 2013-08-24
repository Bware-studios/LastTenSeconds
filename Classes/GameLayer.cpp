//
//  GameLayer.cpp
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#include "GameLayer.h"

const float runinput_target_alfa=0.75;
const float runinput_paso_alfa=1.0;

const CCPoint runbar_topleft=ccp(200,120);
const float runbar_width=300;
const float runbar_height=50;
const ccColor4F runbar_color={0.0,1.0,0,1.0};
const ccColor4F target_color={1.0,0.0,0,1.0};
const ccColor4F hit_color={0,0,1.0,1.0};

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
    
    tnow=0.0;
    runinput_enable();
    reachedbomb_enabled=false;
    jump_enabled=false;
    explosion_enabled=false;
    
    //debug only
    runinput_valueT=CCLabelTTF::create("#", "Marker Felt", 20);
    runinput_valueT->setPosition(ccp(200,200));
    this->addChild(runinput_valueT);
    
    
    countdown_counterT=CCLabelTTF::create("10.0", "Marker Felt", 60);
    countdown_counterT->setPosition(ccp(800,500));
    countdown_counterT->setColor((const ccColor3B){255,0,0});
    addChild(countdown_counterT);
    
    paso=0;
    
    scheduleUpdate();
    return true;
}


bool GameLayer::ccTouchBegan(CCTouch *touch, CCEvent *event) {
//    printf("touch\n");
//    paso+=1;
//    GameScene::theGameScene->unpaso(paso);
    
    if (!runinput_down) {
        runinput_down=true;
        runinput_downalfa=runinput_alfaBar;
    } else {
        runinput_enabled=false;
        jump_enabled=true;
    }
    return true;
}

void GameLayer::ccTouchMoved(CCTouch *touch, CCEvent *event) {
    
}

void GameLayer::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    if (!runinput_up) {
        runinput_up=true;
        runinput_upalfa=runinput_alfaBar;
    }
}

void GameLayer::ccTouchCancelled(CCTouch *touch, CCEvent *event) {
    if (!runinput_up) {
        runinput_up=true;
        runinput_upalfa=runinput_alfaBar;
    }
}

void GameLayer::update(float dt) {
    tnow+=dt;
    char tstring[100];
    
    float counter_time=10-tnow;
    if (counter_time<=0) {
        counter_time=0;
        if (!explosion_enabled) {
            explosion_enabled=true;
            GameScene::theGameScene->start_explossion();
        }
    }
    sprintf(tstring, "%.1f",counter_time);
    countdown_counterT->setString(tstring);
    
    
    if (runinput_enabled) {
        float runinput_dt;
        runinput_dt=tnow-runinput_lastStepTime;
        runinput_alfaBar=runinput_dt/1.0; // 1 bar per second
    
        if (runinput_alfaBar>=runinput_paso_alfa) {
            if (!runinput_up) runinput_upalfa=runinput_paso_alfa;
            if (!runinput_down) runinput_downalfa=runinput_paso_alfa;
            float hit_alfa=0.5*(runinput_downalfa+runinput_upalfa);
            float paso=optimum_step_size*(1-3.0*fabs((hit_alfa-runinput_target_alfa)));
            runinput_doStep();
            GameScene::theGameScene->unpaso(paso);
            //debug
            sprintf(tstring,"%.2f",paso);
            runinput_valueT->setString(tstring);
        }
    }
}

void GameLayer::draw() {
    // draw target
    CCPoint target_tl=ccp(runbar_topleft.x+runbar_width*runinput_target_alfa-3,runbar_topleft.y+3);
    CCPoint target_br=ccp(target_tl.x+6,target_tl.y-6-runbar_height);
    cocos2d::ccDrawSolidRect(target_tl, target_br, target_color);
    
    // draw bar
    CCPoint runbar_bottomright=ccp(runbar_topleft.x+runbar_width*runinput_alfaBar,runbar_topleft.y-runbar_height);
    cocos2d::ccDrawSolidRect(runbar_topleft, runbar_bottomright, runbar_color);
    
    //draw mouse
    if (!runinput_down) return;
    target_tl=ccp(runbar_topleft.x+runinput_downalfa*runbar_width,runbar_topleft.y);
    if (runinput_up) {
        target_br=ccp(runbar_topleft.x+runinput_upalfa*runbar_width,runbar_bottomright.y);
    } else {
        target_br=ccp(runbar_bottomright.x,runbar_bottomright.y);
    }
    cocos2d::ccDrawSolidRect(target_tl, target_br, hit_color);
}

void GameLayer::runinput_enable() {
    runinput_enabled=true;
    runinput_doStep();
}

void GameLayer::runinput_doStep() {
    runinput_lastStepTime=tnow;
    runinput_alfaBar=0;
    runinput_down=false;
    runinput_up=false;
}
