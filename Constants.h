//
// Created by aschethor on 02.11.17.
//

#ifndef PROJECTQM_ND_2_CONSTANTS_H
#define PROJECTQM_ND_2_CONSTANTS_H

static const double H_BAR = 1;
static const double K_B = 1;
static const double T = 1;
static const double BETA = 1/K_B/T;

/**
 * random uniform distribution
 * @return random number between 0 and 1
 */
inline double rand_u(){
    return ((double) rand()/(RAND_MAX));
}

#endif //PROJECTQM_ND_2_CONSTANTS_H