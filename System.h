//
// Created by aschethor on 02.11.17.
//

#ifndef PROJECTQM_ND_2_SYSTEM_H
#define PROJECTQM_ND_2_SYSTEM_H

#include <vector>
#include "Particle.h"

class System {
public:

    //tmp terms needed in order to reverse steps

    double internal_term,internal_term_tmp;//sum over interaction terms
    double external_term,external_term_tmp;//sum over external potential terms
    double kinetic_term,kinetic_term_tmp;//sum over kinetic terms

    vector<double> internal_terms,internal_terms_tmp;//interaction terms

    vector<Particle> particles;
    vector<void (*)(System)> observables;

    System();
    void add_particle(Particle particle);
    void add_observable(void (*observable)(System));

    double update_kinetic_term();
    double update_internal_term();
    double update_external_term();

    double probability();//calculate probability
    void step();//make random step
    void accept();//accept step (cpy values into tmp)
    void reject();//reverse step (restore values from tmp)
};


#endif //PROJECTQM_ND_2_SYSTEM_H
