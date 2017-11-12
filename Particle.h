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
    //double charge;
    //char element;

    vector<Bead> beads;

    Particle(double mass,int nBeads,double (*external_potential)(Bead bead));

    Bead get_bead(int numerator,int denominator);
    double kinetic_term();
    double potential_term();
    double (*external_potential)(Bead bead);
    //double (*internal_potential)(Particle particle);//later... maybe better: depends on Bead -> get_bead()
    virtual void step(vector<double> randoms);
};


#endif //PROJECTQM_ND_2_PARTICLE_H
