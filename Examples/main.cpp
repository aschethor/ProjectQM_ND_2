#include <iostream>
#include <math.h>
#include <time.h>
#include "../Particle.h"
#include "../System.h"
#include "../Utils.h"
#include <fstream>

using namespace std;

ofstream output_file;

void observable(System& system){
    // cout<<"here in observable: ";
    for(int i=0;i<system.particles[0].beads.size();i++){
        //cout<<system.particles[0].beads[i].x<<" ";
        output_file<<""<<system.particles[0].beads[i].x<<endl;
    }
}

double external_potential(Bead bead){
    double w = 1;
    return w*w/2*bead.x*bead.x;
}

double my_calc_external_term(Particle& particle){
    int n = particle.beads.size();
    double term = 0;
    for(int i=0;i<n;i++){
        term += external_potential(particle.beads[i]);
    }
    return term/n;
}

double my_calc_internal_term(Particle& particle1,Particle& particle2){
    return 0;
}

inline int min(int a,int b){
    return a<b?a:b;
}

/*
 * steps with "modes"
 * -> much better convergence
 */
void my_step_1D(Particle* particle,vector<double> randoms){
    if(randoms.size()==0){
        double alpha = 1;
        double x = (rand_u()*2-1)*alpha;

        // excite "modes" of bead-ring
        // int mode = min(-(int)log2(rand_u()),particle->beads.size()/2);
        int mode = get_mode(particle->beads.size()/2);
        // cout<<" excited mode: "<<mode<<endl;
        double phase = rand_u()*M_PI/2;
        for(int i=0;i<particle->beads.size();i++){
            double factor = sin(i*mode*2*M_PI/particle->beads.size()+phase);
            particle->beads[i].x += factor*x;
        }
    }
}

/*
 * "naive" step-approach
 */
void my_step_1D_naive(Particle *particle, vector<double> randoms){
    if(randoms.size()==0){
        double alpha = 1;
        int bead = min(rand_u()*particle->beads.size(),particle->beads.size()-1);
        particle->beads[bead].x += alpha*(rand_u()*2-1);
    }
}

int main() {
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\harmonic_oscillator_qm.csv");
    srand (time(NULL));
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.add_particle(Particle(1,'x',40,&my_step_1D));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(50000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
    return 0;
}