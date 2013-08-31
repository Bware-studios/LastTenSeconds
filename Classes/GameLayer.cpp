//
//  GameLayer.cpp
//  ld27
//
//  Created by Mikel on 24/08/13.
//
//

#include "GameLayer.h"


// runinput constants
// time per step animation
const float step_time=0.5;
const float runinput_alfa_persecond=2.0; // in 0.5s full bar
const float runinput_alfa_min_fall=1.0; // with alfa more than this fall instead of step
const float runinput_alfa_min_jump=1.4; // with alfa more than this jump instead of fall


const float slowmotion_factor=0.5;

const float runinput_target_alfa=1.0;




const CCPoint runbar_topleft=ccp(200,baseline_height-30);
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
    //this->setKeypadEnabled(true);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    tnow=0.0;
    runinput_enable();
    reachedbomb_enabled=false;
    jump_enabled=false;
    explossion_started=false;
    
    //debug only
    runinput_valueT=CCLabelTTF::create("#", "Marker Felt", 20);
    runinput_valueT->setPosition(ccp(900,baseline_height-50));
    this->addChild(runinput_valueT);
    
    
    countdown_counterT=CCLabelTTF::create("10.0", "Marker Felt", 60);
    countdown_counterT->setPosition(ccp(800,baseline_height+470));
    countdown_counterT->setColor((const ccColor3B){255,0,0});
    addChild(countdown_counterT);

    
    runinput_step_inputready=false;
    runinput_onstep_anim=false;
    runinput_currentstep_finish_time=0.0;    
    runinput_stepx=0;

    
    paso=0;
    beginning=true;
    first_step=false;

    on_step=false;
    runinput_stepdone=false;

    current_slowmotion_factor=slowmotion_factor;
    
    scheduleUpdate();
    return true;
}


bool GameLayer::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    if (runinput_enabled && !runinput_down && !runinput_step_inputready) {
        runinput_down=true;
        runinput_alfaBar=0.0;
        runinput_step_inputready=false;
        runinput_stepx=0.0;
        
//        runinput_down_time=tnow;
//        runinput_stepdone=false;
    }
    return true;
}

void GameLayer::ccTouchMoved(CCTouch *touch, CCEvent *event) {
    
}

void GameLayer::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    if (runinput_down) {
        runinput_down=false;
        runinput_step_inputready=true;
        if (!runinput_onstep_anim) {
            runinput_tryNewStep();
        }
    }
}

void GameLayer::ccTouchCancelled(CCTouch *touch, CCEvent *event) {
    if (runinput_down) {
        runinput_down=false;
        runinput_step_inputready=true;
        if (!runinput_onstep_anim) {
            runinput_tryNewStep();
        }
    }
}

void GameLayer::update(float dt) {
    tnow+=dt;
    tgame+=dt*current_slowmotion_factor;
    char tstring[100];
    // counter update
    float counter_time=10-tgame;
    if (counter_time<=0) {
        counter_time=0;
        if (!explossion_started) {
            explossion_started=true;
            runinput_enabled=false;
            GameScene::theGameScene->start_explossion();
        }
    } else {
        GameScene::theGameScene->check_win();
    }
    sprintf(tstring, "%.1f",counter_time);
    countdown_counterT->setString(tstring);
    
    
    if (runinput_enabled) {
        if (runinput_down) {
            runinput_alfaBar+=dt*runinput_alfa_persecond;
            runinput_stepx=runinput_alfaBar*optimum_step_size;
            
            sprintf(tstring,"%.2f %.2f",runinput_alfaBar,runinput_stepx);
            runinput_valueT->setString(tstring);
        }
        
        if (runinput_onstep_anim && tnow>runinput_currentstep_finish_time) {
            runinput_onstep_anim=false;
            if (runinput_step_inputready) {
                runinput_tryNewStep();
            }
        }
        
        
//        if (on_step) {
//            if ( tnow>runinput_lastStepTime+step_time*slowmotion_factor )
//                on_step=false;
//        }
//        if (!on_step) {
//        
//            if ( runinput_step ) {
//                if (runinput_alfaBar>0.5) {
//                    GameScene::theGameScene->fall();
//                    runinput_enabled=false;
//                } else {
//                    GameScene::theGameScene->unpaso(paso);
//                    runinput_lastStepTime=tnow;
//                    paso=0;
//                    on_step=true;
//                }
//            }
//        }
//        }
//    
//        if ( tnow>runinput_lastStepTime+step_time*slowmotion_factor ) {
//            if (!beginning) {
//                if (runinput_down)
//                GameScene::theGameScene->fall();
//                runinput_enabled=false;
//            } else {
//                runinput_lastStepTime=tnow;
//                paso=0;
//                GameScene::theGameScene->unpaso(paso);
//            }
//        }
        
//        if (runinput_alfaBar>=runinput_paso_alfa) {
//            if (!runinput_up) runinput_upalfa=runinput_paso_alfa;
//            if (!runinput_down) runinput_downalfa=runinput_paso_alfa;
//            float hit_alfa=0.5*(runinput_downalfa+runinput_upalfa);
//            float paso=optimum_step_size*(1-3.0*fabs((hit_alfa-runinput_target_alfa)))*slowmotion_factor;
//            if (paso<10) paso=10;
//            //runinput_doStep();
//            //GameScene::theGameScene->unpaso(paso);
//            //debug
//            sprintf(tstring,"%.2f",paso);
//            runinput_valueT->setString(tstring);
        }
}

void GameLayer::draw() {
    // draw target
    CCPoint target_tl=ccp(runbar_topleft.x+runbar_width*runinput_target_alfa-3,runbar_topleft.y+3);
    CCPoint target_br=ccp(target_tl.x+6,target_tl.y-6-runbar_height);
    cocos2d::ccDrawSolidRect(target_tl, target_br, target_color);
    
    // draw bar
//    CCPoint runbar_bottomright=ccp(runbar_topleft.x+runbar_width*runinput_alfaBar,runbar_topleft.y-runbar_height);
//    cocos2d::ccDrawSolidRect(runbar_topleft, runbar_bottomright, runbar_color);
    
    float draw_alfa;
    draw_alfa=runinput_alfaBar<runinput_alfa_min_fall?runinput_alfaBar:runinput_alfa_min_fall;
    
    if (runinput_down) {
        CCPoint runbar_bottomright=ccp(runbar_topleft.x+runbar_width*draw_alfa,runbar_topleft.y-runbar_height);
        cocos2d::ccDrawSolidRect(runbar_topleft, runbar_bottomright, runbar_color);
    }
    if (runinput_step_inputready) {
        CCPoint runbar_bottomright=ccp(runbar_topleft.x+runbar_width*draw_alfa,runbar_topleft.y-runbar_height);
        cocos2d::ccDrawSolidRect(runbar_topleft, runbar_bottomright, hit_color);
    }
    if ( (runinput_down || runinput_step_inputready) && runinput_alfaBar>runinput_alfa_min_fall ) {
        draw_alfa=runinput_alfaBar<runinput_alfa_min_jump?runinput_alfaBar:runinput_alfa_min_jump;
        CCPoint runbar_bottomright=ccp(runbar_topleft.x+runbar_width*draw_alfa,runbar_topleft.y-runbar_height);
        cocos2d::ccDrawSolidRect(ccp(runbar_topleft.x+runbar_width,runbar_topleft.y), runbar_bottomright, target_color);
    }
    if ( (runinput_down || runinput_step_inputready) && runinput_alfaBar>runinput_alfa_min_jump ) {
        draw_alfa=runinput_alfa_min_jump+0.2;
        CCPoint runbar_bottomright=ccp(runbar_topleft.x+runbar_width*draw_alfa,runbar_topleft.y-runbar_height);
        cocos2d::ccDrawSolidRect(ccp(runbar_topleft.x+runbar_width*runinput_alfa_min_jump,runbar_topleft.y), runbar_bottomright, runbar_color);
    }
//    draw_alfa=runinput_alfaBar<runinput_alfa_min_jump?runinput_alfaBar:runinput_alfa_min_fall;
//    if (runinput_down) {
//        CCPoint runbar_bottomright=ccp(runbar_topleft.x+runbar_width*draw_alfa,runbar_topleft.y-runbar_height);
//        cocos2d::ccDrawSolidRect(runbar_topleft, runbar_bottomright, runbar_color);
//    }
//
    
    //draw mouse
//    if (!runinput_down) return;
//    target_tl=ccp(runbar_topleft.x+runinput_downalfa*runbar_width,runbar_topleft.y);
//    if (runinput_up) {
//        target_br=ccp(runbar_topleft.x+runinput_upalfa*runbar_width,runbar_bottomright.y);
//    } else {
//        target_br=ccp(runbar_bottomright.x,runbar_bottomright.y);
//    }
//    cocos2d::ccDrawSolidRect(target_tl, target_br, hit_color);
}

void GameLayer::runinput_enable() {
    runinput_enabled=true;
    runinput_down=false;
}

void GameLayer::runinput_tryNewStep() {
    runinput_step_inputready=false;
    if (runinput_alfaBar<runinput_alfa_min_fall) { // step
        runinput_onstep_anim=true;
        runinput_currentstep_finish_time=tnow+step_time;
        GameScene::theGameScene->step(runinput_stepx);
    } else if (runinput_alfaBar<runinput_alfa_min_jump) { // fall
        GameScene::theGameScene->fall();
        runinput_enabled=false;
        runinput_step_inputready=false;
        runinput_down=false;
        current_slowmotion_factor=1.0;
    } else { // jump
        GameScene::theGameScene->jump();
        runinput_enabled=false;
        runinput_step_inputready=false;
        runinput_down=false;
    }

}

void GameLayer::recover_from_fall() {
    runinput_enabled=true;
}


