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
    double mass;
    char element;

    vector<Bead> beads;

    Particle(double mass,char element,int nBeads);
    Particle(double mass,char element,int nBeads,void (*step)(Particle* particle,vector<double> randoms));
    Particle(double mass,char element,int nBeads,void (*step)(Bead* bead,vector<double> randoms));
    Particle(double mass,char element,int nBeads,void (*step_particle)(Particle* particle,vector<double> randoms),void (*step_bead)(Bead* bead,vector<double> randoms));

    double kinetic_term();

    void (*step)(Particle* particle,vector<double> randoms);
    void accept();
    void reject();
};


#endif //PROJECTQM_ND_2_PARTICLE_H
