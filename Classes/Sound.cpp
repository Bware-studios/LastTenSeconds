//
//  Sound.cpp
//  ld27
//
//  Created by Mikel on 25/08/13.
//
//

#include "Sound.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

const char *sound_explosion_name="explosion.mp3";
const char *sound_alarm_name="alarm.mp3";

const char *sound_slowmotionsong_name="chariots.mp3";

SimpleAudioEngine *audio_engine;

int song_id;
bool song_playing=false;

int alarm_id;
bool alarm_playing=false;


void sound_preload_all() {
    audio_engine->preloadEffect(sound_slowmotionsong_name);
    audio_engine->preloadEffect(sound_explosion_name);    
}

void sound_play_effect(const char *name) {
    audio_engine->playEffect(name);
}

void sound_play_slowmotionsong() {
    song_id=audio_engine->playEffect(sound_slowmotionsong_name);
    song_playing=true;
}

void sound_stop_slowmotionsong() {
    if (song_playing) {
        audio_engine->stopEffect(song_id);
    }
    song_playing=false;
}


void sound_play_alarm() {
    alarm_id=audio_engine->playEffect(sound_alarm_name,true);
    alarm_playing=true;
}

void sound_stop_alarm() {
    if (alarm_playing) {
        audio_engine->stopEffect(alarm_id);
    }
    alarm_playing=false;
}
