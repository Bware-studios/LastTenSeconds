//
//  Sound.h
//  ld27
//
//  Created by Mikel on 25/08/13.
//
//

#ifndef __ld27__Sound__
#define __ld27__Sound__

#include "common.h"
extern const char *sound_explosion_name;

void sound_preload_all();
void sound_play_effect(const char *name);

void sound_play_slowmotionsong();
void sound_stop_slowmotionsong();

#endif /* defined(__ld27__Sound__) */
