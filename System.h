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

    vector<double> internal_terms,internal_terms_tmp;//interaction terms
    double internal_term,internal_term_tmp;//sum over interaction terms
    vector<double> external_terms,external_terms_tmp;//external terms
    double external_term,external_term_tmp;//sum over external potential terms
    vector<double> kinetic_terms,kinetic_terms_tmp;//sum over kinetic terms
    double kinetic_term,kinetic_term_tmp;//sum over kinetic terms

    int n_accepted,n_rejected;

    vector<Particle> particles;
    vector<void (*)(System&)> observables;

    System();
    System(double (*calc_internal_term)(Particle&,Particle&),double (*calc_external_term)(Particle&));
    System(double (*calc_internal_term)(Particle&,Particle&),double (*calc_external_term)(Particle&),void (*step)(System*));

    void add_particle(Particle particle);
    void add_observable(void (*observable)(System&));

    double (*calc_internal_term)(Particle& particle1,Particle& particle2);//calculate interaction term. Should be commutative! (introduce standard)
    double (*calc_external_term)(Particle& particle);//calculate external potential term (introduce standard)

    void monte_carlo(int n_steps);//make n_steps monte carlo steps

    double probability();//calculate probability
    void (*step)(System*);//make random step
    void accept();//accept step (cpy values into tmp)
    void reject();//reverse step (restore values from tmp)
};


#endif //PROJECTQM_ND_2_SYSTEM_H
