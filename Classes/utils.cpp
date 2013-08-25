//
//  utils.c
//  ld27
//
//  Created by Mikel on 25/08/13.
//
//

#include "utils.h"


float r_unif(float a, float b) {
    return a+(b-a)*CCRANDOM_0_1();
}

