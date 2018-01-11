
#ifndef PROJECTQM_ND_2_SYSTEM_H
#define PROJECTQM_ND_2_SYSTEM_H

#include <vector>
#include "Particle.h"
#include "Utils.h"

class System {

private:

    //reduced planck constant
    double H_BAR = 1;
    //boltzmann constant
    double K_B = 1;
    //temperature of system
    double T = 0.1;
    //thermodynamical beta
    double BETA = 1/K_B/T;

public:

    //potential / interaction terms: the tmp (temporary) terms are needed in to reverse steps in case of rejection
    //interaction terms between particles
    vector<double> internal_terms,internal_terms_tmp;
    //sum over all interaction terms
    double internal_term,internal_term_tmp;
    //external potential terms
    vector<double> external_terms,external_terms_tmp;
    //sum over external potential terms
    double external_term,external_term_tmp;
    //kinetic energy terms
    vector<double> kinetic_terms,kinetic_terms_tmp;
    //sum over kinetic terms
    double kinetic_term,kinetic_term_tmp;

    //number of accepted and rejected samples (useful for analysis / debugging)
    int n_accepted,n_rejected;

    //particles of the system
    vector<Particle> particles;

    //observables of system (functions that are called after each monte carlo step to store observation in file)
    vector<void (*)(System&)> observables;

    System();
    System(double (*calc_internal_term)(Particle&,Particle&),double (*calc_external_term)(Particle&));
    System(double (*calc_internal_term)(Particle&,Particle&),double (*calc_external_term)(Particle&),void (*step)(System*));

    //add particle to system
    void add_particle(Particle particle);
    //add observable to system
    void add_observable(void (*observable)(System&));

    //calculate interaction term between 2 particles. Should be commutative!
    double (*calc_internal_term)(Particle& particle1,Particle& particle2);
    //calculate external potential term
    double (*calc_external_term)(Particle& particle);

    //make n_steps monte carlo steps
    void monte_carlo(int n_steps);

    //calculate probability of current system configuration
    double probability();
    //make random step (can be replaced by custom stepping technique)
    void (*step)(System*);
    //accept step (cpy values into tmp - variables)
    void accept();
    //reverse step (restore values from tmp - variables)
    void reject();

    //set temperature of system
    void set_T(double T){
        this->T=T;
        this->BETA = 1/K_B/T;
    }

    //set h_bar of system
    void set_H_BAR(double H_BAR){
        this->H_BAR = H_BAR;
    }

    //set boltzmann constant of system
    void set_K_B(double K_B){
        this->K_B = K_B;
        this->BETA = 1/K_B/T;
    }
};

#endif //PROJECTQM_ND_2_SYSTEM_H