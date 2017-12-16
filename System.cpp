//
// Created by aschethor on 02.11.17.
//

#include "System.h"
#include <math.h>
#include <cstdlib>
#include <iostream>
#include "Utils.h"

using namespace std;

void _step(System* system){
    int n = system->particles.size();
    int i = (int)(rand_u()*n)%n;

    system->particles[i].step(&(system->particles[i]),vector<double>());

    //external potential
    system->external_term -= system->external_terms[i];
    system->external_terms[i] = system->calc_external_term(system->particles[i]);
    system->external_term += system->external_terms[i];

    //internal (interaction) potentials
    int offset = i*(i-1)/2;
    for(int j=0;j<i;j++){
        int index = offset + j;
        system->internal_term -= system->internal_terms[index];
        system->internal_terms[index] = system->calc_internal_term(system->particles[i],system->particles[j]);
        system->internal_term += system->internal_terms[index];
    }
    for(int j=i;j<system->particles.size()-1;j++){
        int index = i+j*(j+1)/2;
        system->internal_term -= system->internal_terms[index];
        system->internal_terms[index] = system->calc_internal_term(system->particles[i],system->particles[j]);
        system->internal_term += system->internal_terms[index];
    }

    //kinetic term
    system->kinetic_term -= system->kinetic_terms[i];
    system->kinetic_terms[i] = system->particles[i].kinetic_term();
    system->kinetic_term += system->kinetic_terms[i];
}

double _calc_external_term(Particle& particle){
    return 0;
}

double _calc_internal_term(Particle& particle1,Particle& particle2){
    return 0;
}

System::System() {
    n_accepted = 0;
    n_rejected = 0;
    kinetic_term = kinetic_term_tmp = 0;
    external_term = external_term_tmp = 0;
    internal_term = internal_term_tmp = 0;
    this->calc_internal_term = _calc_internal_term;
    this->calc_external_term = _calc_external_term;
    this->step = &_step;
}

System::System(double (*calc_internal_term)(Particle&,Particle&),double (*calc_external_term)(Particle&)) {
    n_accepted = 0;
    n_rejected = 0;
    kinetic_term = kinetic_term_tmp = 0;
    external_term = external_term_tmp = 0;
    internal_term = internal_term_tmp = 0;
    this->calc_internal_term = calc_internal_term;
    this->calc_external_term = calc_external_term;
    this->step = &_step;
}

System::System(double (*calc_internal_term)(Particle&, Particle&), double (*calc_external_term)(Particle&),void (*step)(System *)) {
    n_accepted = 0;
    n_rejected = 0;
    kinetic_term = kinetic_term_tmp = 0;
    external_term = external_term_tmp = 0;
    internal_term = internal_term_tmp = 0;
    this->calc_internal_term = calc_internal_term;
    this->calc_external_term = calc_external_term;
    this->step = step;
}

void System::add_particle(Particle particle) {
    external_terms.push_back(0);
    external_terms_tmp.push_back(0);
    for(int i=0;i<particles.size();i++){
        internal_terms.push_back(0);
        internal_terms_tmp.push_back(0);
    }
    kinetic_terms.push_back(0);
    kinetic_terms_tmp.push_back(0);
    particles.push_back(particle);
}

void System::add_observable(void (*observable)(System&)) {
    observables.push_back(observable);
}

void System::monte_carlo(int n_steps) {
    n_accepted = n_rejected = 0;
    double prob = probability();
    // cout<<"monte carlo: prob: "<<prob;

    for(int i=0;i<n_steps;i++){
        step(this);
        double probability_tmp = probability();
        // cout<<" new prob: "<<probability_tmp<<endl;
        if(rand_u() < (probability_tmp/prob)){
            accept();
            prob = probability_tmp;
        }else{
            reject();
        }
        for(int j=0;j<observables.size();j++){
            observables[j](*this);
        }
    }
}

double System::probability() {
    return exp(-kinetic_term/BETA/H_BAR/2-BETA*(internal_term+external_term));
}

void System::reject() {
    n_rejected++;
    for(int i=0;i<particles.size();i++){
        particles[i].reject();
    }
    internal_term = internal_term_tmp;
    external_term = external_term_tmp;
    kinetic_term = kinetic_term_tmp;
    for(int i=0;i<internal_terms.size();i++){
        internal_terms[i]=internal_terms_tmp[i];
    }
    for(int i=0;i<external_terms.size();i++){
        external_terms[i]=external_terms_tmp[i];
    }
    for(int i=0;i<kinetic_terms.size();i++){
        kinetic_terms[i]=kinetic_terms_tmp[i];
    }
}

void System::accept() {
    n_accepted++;
    for(int i=0;i<particles.size();i++){
        particles[i].accept();
    }
    internal_term_tmp = internal_term;
    external_term_tmp = external_term;
    kinetic_term_tmp = kinetic_term;
    for(int i=0;i<internal_terms.size();i++){
        internal_terms_tmp[i]=internal_terms[i];
    }
    for(int i=0;i<external_terms.size();i++){
        external_terms_tmp[i]=external_terms[i];
    }
    for(int i=0;i<kinetic_terms.size();i++){
        kinetic_terms_tmp[i]=kinetic_terms[i];
    }
}