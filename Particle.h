//
// Created by aschethor on 02.11.17.
//

#ifndef PROJECTQM_ND_2_PARTICLE_H
#define PROJECTQM_ND_2_PARTICLE_H

#include <vector>
#include "Bead.h"

using namespace std;

class Particle {
public:
    //mass of particle
    double mass;
    //character to specify element (can later be used give particles e.g. charge in the interaction term)
    char element;

    //beads of particle describing a closed path for the feynman path integral
    vector<Bead> beads;

    Particle(double mass,char element,int nBeads);
    Particle(double mass,char element,int nBeads,void (*step)(Particle* particle,vector<double> randoms));
    Particle(double mass,char element,int nBeads,void (*step)(Bead* bead,vector<double> randoms));
    Particle(double mass,char element,int nBeads,void (*step_particle)(Particle* particle,vector<double> randoms),void (*step_bead)(Bead* bead,vector<double> randoms));

    //kinetic term
    double kinetic_term();

    //mode step of particle in 3 dimensions (can be replaced by custom stepping technique)
    void (*step)(Particle* particle,vector<double> randoms);
    //called if monte carlo step accepted
    void accept();
    //called if monte carlo step rejected
    void reject();
};

#endif //PROJECTQM_ND_2_PARTICLE_H
