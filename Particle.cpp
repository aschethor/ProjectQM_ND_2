//
// Created by aschethor on 02.11.17.
//

#include <iostream>
#include "Particle.h"

Particle::Particle(double mass,int nBeads,double (*external_potential)(Bead bead)) {
    this->mass = mass;
    this->external_potential = external_potential;
    for(int i=0;i<nBeads;i++){
        beads.push_back(Bead());
    }
}

Bead Particle::get_bead(int numerator, int denominator) {
    //idea: interpolate between beads etc (later)
    //if(denominator!=beads.size()) -> error
    return beads[numerator];
}

double Particle::kinetic_term() {
    int n = beads.size();
    double kinetic_term = beads[0].distance_squared(beads[n-1]);
    for(int i=1;i<n;i++){
        kinetic_term += beads[i].distance_squared(beads[i-1]);
    }
    return n*mass*kinetic_term;
}

double Particle::potential_term() {
    int n = beads.size();
    double potential = 0;
    for(int i=0;i<n;i++){
        potential += external_potential(beads[i]);
    }
    return potential/n;
}

void Particle::step(vector<double> randoms) {
    std::cout << "Particle step" << std::endl;
}