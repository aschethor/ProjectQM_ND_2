//
// Created by aschethor on 02.11.17.
//

#ifndef PROJECTQM_ND_2_SYSTEM_H
#define PROJECTQM_ND_2_SYSTEM_H

#include <vector>
#include "Particle.h"

class System {
public:
    vector<Particle> particles;
    vector<void (*)(System)> observables;

    System();
    void add_particle(Particle particle);
    void add_observable(void (*observable)(System));

    double kinetic_term();
    double potential_term();
    double probability();
    void step();
};


#endif //PROJECTQM_ND_2_SYSTEM_H
