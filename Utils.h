//
// Created by aschethor on 02.11.17.
//

#ifndef PROJECTQM_ND_2_UTILS_H
#define PROJECTQM_ND_2_UTILS_H

#include <math.h>

/**
 * random uniform distribution
 * @return random number between 0 and 1
 */
inline double rand_u(){
    return ((double) rand()/(RAND_MAX));
}

inline int get_mode(int max){
    if(max == 0) return 0;
    if(rand_u()<0.25)return 0;
    else return 1+get_mode(max-1);
}

inline bool min(double a,double b){
    return a<b?a:b;
}

#endif //PROJECTQM_ND_2_UTILS_H