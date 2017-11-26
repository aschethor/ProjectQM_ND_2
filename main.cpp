#include <iostream>
#include <math.h>
#include <time.h>
#include "Particle.h"
#include "System.h"
#include "Constants.h"

using namespace std;

void observable(System& system){
    cout<<"here in observable: ";
    for(int i=0;i<system.particles[0].beads.size();i++)
        cout<<system.particles[0].beads[i].x<<" ";
    cout<<endl;
}

double external_potential(Bead bead){
    double w = 0.1;
    return w*bead.x*bead.x;
}

double my_calc_external_term(Particle& particle){
    int n = particle.beads.size();
    double term = 0;
    for(int i=0;i<n;i++){
        term += external_potential(particle.beads[i]);
    }
    return term*BETA/n;
}

double my_calc_internal_term(Particle& particle1,Particle& particle2){
    return 0;
}

inline int min(int a,int b){
    return a<b?a:b;
}

void my_step_1D(Particle* particle,vector<double> randoms){
    if(randoms.size()==0){
        // generate random uniform spherical distribution
        double phi = rand_u()*2*M_PI;
        double x = cos(phi);

        // multiply by alpha
        double alpha = rand_u()*2;
        x *= alpha;

        // excite "modes" of bead-ring
        int mode = min(-(int)log2(rand_u()),particle->beads.size()/2);
        // cout<<" excited mode: "<<mode<<endl;
        double phase = rand_u()*M_PI/2;
        for(int i=0;i<particle->beads.size();i++){
            double factor = sin(i*mode*2*M_PI/particle->beads.size()+phase);
            vector<double> randoms;
            // cout<<"make step: "<<factor*x<<" mode "<<mode<<" phase "<<phase<<" factor "<<factor<<endl;
            randoms.push_back(factor*x);
            randoms.push_back(0);
            randoms.push_back(0);
            particle->beads[i].step(&particle->beads[i],randoms);
        }
    }
}

int main() {
    srand (time(NULL));
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.add_particle(Particle(1,'x',20,&my_step_1D));
    system.add_observable(&observable);
    system.monte_carlo(100);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    return 0;
}