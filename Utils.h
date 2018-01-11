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

/**
 * mode to excite:
 * this returns i with probability P(i) following approximately the following distribution:
 *  P(i) = N*(0.75)^i   for 0<=i<=max, where N is a normalization constant
 *  P(i) = 0            for i<0 or i>max
 * @param max maximum mode to return
 * @return mode
 */
inline int get_mode(int max){
    if(max == 0) return 0;
    if(rand_u()<0.25)return 0;
    else return 1+get_mode(max-1);
}

/**
 * self explaining... ;)
 * @param a
 * @param b
 * @return min(a,b)
 */
inline int min(int a,int b){
    return a<b?a:b;
}

#endif //PROJECTQM_ND_2_UTILS_H