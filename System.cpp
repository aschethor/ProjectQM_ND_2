//
// Created by aschethor on 02.11.17.
//

#include "System.h"
#include <math.h>
#include "Constants.h"

System::System() {

}

void System::add_particle(Particle particle) {
    particles.push_back(particle);
}

void System::add_observable(void (*observable)(System)) {
    observables.push_back(observable);
}

double System::kinetic_term() {
    double kinetic = 0;
    for(int i=0;i<particles.size();i++){
        kinetic+=particles[i].kinetic_term();
    }
    return kinetic/BETA/H_BAR;
}

double System::update_external_term() {
    double potential = 0;
    for(int i=0;i<particles.size();i++){
        potential+=particles[i].potential_term();
    }
    return potential*BETA;
}

double System::probability() {
    return exp(-kinetic_term-internal_term-external_term);
}

void System::step() {
    //TODO: MC-step
    for(int i;i<observables.size();i++){
        observables[i](*this);
    }
}

void System::reject() {

}