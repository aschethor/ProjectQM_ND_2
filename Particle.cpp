
#include <iostream>
#include "Particle.h"
#include "Utils.h"
#include <math.h>

/**
 * standard stepping technique of particles using 3d mode stepping:
 *  - choose direction and amplitude of mode displacement
 *  - choose mode to displace
 *  - displace beads according to chosen parameters
 * @param particle particle to displace
 * @param randoms evt. further parameters (not used here)
 */
void _step(Particle* particle,vector<double> randoms){
    if(randoms.size()==0){
        // generate random uniform spherical distribution
        double phi = rand_u()*2*M_PI;
        double theta = acos(rand_u()*2-1);
        double x = sin(theta)*cos(phi);
        double y = sin(theta)*sin(phi);
        double z = cos(theta);

        // multiply by alpha
        double alpha = rand_u()*1;
        x *= alpha;
        y *= alpha;
        z *= alpha;

        // excite "modes" of bead-ring
        int mode = get_mode(particle->beads.size()/2);
        double phase = rand_u()*M_PI/2;
        for(int i=0;i<particle->beads.size();i++){
            double factor = sin(i*mode*2*M_PI/particle->beads.size()+phase);
            particle->beads[i].x += factor*x;
            particle->beads[i].y += factor*y;
            particle->beads[i].z += factor*z;
        }
    }
}

Particle::Particle(double mass, char element, int nBeads) {
    this->mass = mass;
    this->element = element;
    for(int i=0;i<nBeads;i++){
        beads.push_back(Bead());
    }
    this->step = _step;
}

Particle::Particle(double mass, char element, int nBeads, void (*step_particle)(Particle *, vector<double>)) {
    this->mass = mass;
    this->element = element;
    for(int i=0;i<nBeads;i++){
        beads.push_back(Bead());
    }
    this->step = step_particle;
}

Particle::Particle(double mass, char element, int nBeads, void (*step_bead)(Bead *, vector<double>)) {
    this->mass = mass;
    this->element = element;
    for(int i=0;i<nBeads;i++){
        beads.push_back(Bead(step_bead));
    }
    this->step = _step;
}

Particle::Particle(double mass, char element, int nBeads, void (*step_particle)(Particle *, vector<double>),
                   void (*step_bead)(Bead *, vector<double>)) {
    this->mass = mass;
    this->element = element;
    for(int i=0;i<nBeads;i++){
        beads.push_back(Bead(step_bead));
    }
    this->step = step_particle;
}

/**
 * calculate kinetic term from bead distances
 * @return kinetic term
 */
double Particle::kinetic_term() {
    int n = beads.size();
    double kinetic_term = beads[0].distance_squared(beads[n-1]);
    for(int i=1;i<n;i++){
        kinetic_term += beads[i].distance_squared(beads[i-1]);
    }
    return n*mass*kinetic_term;
}

void Particle::reject() {
    for(int i=0;i<beads.size();i++){
        beads[i].reject();
    }
}

void Particle::accept() {
    for(int i=0;i<beads.size();i++){
        beads[i].accept();
    }
}