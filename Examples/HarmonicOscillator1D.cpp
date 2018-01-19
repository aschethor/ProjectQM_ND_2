#include <iostream>
#include <math.h>
#include <time.h>
#include "../Particle.h"
#include "../System.h"
#include "../Utils.h"
#include <fstream>

using namespace std;

// file to write the observations
ofstream output_file;

// observable function (writes observations into output_file)
void observable(System& system){
    // cout<<"here in observable: ";
    for(int i=0;i<system.particles[0].beads.size();i++){
        //cout<<system.particles[0].beads[i].x<<" ";
        output_file<<""<<system.particles[0].beads[i].x<<endl;
    }
}

// definition of the external potential
double external_potential(Bead bead){
    double w = 1;
    return w*w/2*bead.x*bead.x;
}

// this function needs to be passed to the system and is needed to calculate the external potential
double my_calc_external_term(Particle& particle){
    int n = particle.beads.size();
    double term = 0;
    for(int i=0;i<n;i++){
        term += external_potential(particle.beads[i]);
    }
    return term/n;
}

// this function could be used to calculate the interaction terms between particles (see e.g. ProductInteraction.cpp)
double my_calc_internal_term(Particle& particle1,Particle& particle2){
    return 0;
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
void my_step_1D_2(Particle *particle, vector<double> randoms){
    if(randoms.size()==0){
        double alpha = 1;
        int bead = min(rand_u()*particle->beads.size(),particle->beads.size()-1);
        particle->beads[bead].x += alpha*(rand_u()*2-1);
    }
}

/*
 * "advanced naive" step-approach with displacements of the whole ring
 */
void my_step_1D_3(Particle *particle, vector<double> randoms){
    if(randoms.size()==0){
        double alpha = 1;
        if(rand_u()<0.15){ // -> shift all beads
            double shift = alpha * (rand_u() * 2 - 1);
            for(int i=0;i<particle->beads.size();i++){
                particle->beads[i].x += shift;
            }
        }else { // -> only shift one bead (bead)
            int bead = min(rand_u() * particle->beads.size(), particle->beads.size() - 1);
            particle->beads[bead].x += alpha * (rand_u() * 2 - 1);
        }
    }
}

// use only one bead for the particle to obtain classical results
void classic_harmonic_oscillator(){
    cout<<"classical... ";
    //open file for observables
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\harmonic_oscillator_cl.csv");
    //create "physical" system and specify internal / external term
    System system(&my_calc_internal_term,&my_calc_external_term);
    //set temperature of the system to 0.1
    system.set_T(0.1);
    //add a particle to the system (in this case: mass = 1, "element" = 'x', #beads = 1, stepping technique: mode)
    system.add_particle(Particle(1,'x',1,&my_step_1D));
    //make 1000 random monte carlo steps to initialize system
    system.monte_carlo(1000);
    //add observable to the system -> from now on, this function will be called after each MC step
    system.add_observable(&observable);
    //sample 500000 MCMC steps
    system.monte_carlo(500000);
    //check if step size was ok by comparing number of accepted / rejected samples
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    //close file for observables
    output_file.close();
}

// using 40 beads, one obtains in very good approximation the correct quantum results
void quantum_harmonic_oscillator(){
    cout<<"quantum mode... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\harmonic_oscillator_qm.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.set_T(0.1);
    //here we're using 40 beads...
    system.add_particle(Particle(1,'x',40,&my_step_1D));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(50000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}

void naive_quantum_harmonic_oscillator(){
    cout<<"naive... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\harmonic_oscillator_qm_naive.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.set_T(0.1);
    //here we're using the "naive" stepping technique
    system.add_particle(Particle(1,'x',40, &my_step_1D_2));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(50000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}

// sometimes returns really weird results (looks more classical) ... probably needs more steps in order to converge
void advanced_naive_quantum_harmonic_oscillator(){
    cout<<"advanced naive... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\harmonic_oscillator_qm_adv_naive.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.set_T(0.1);
    //here we're using the "advanced naive" stepping technique
    system.add_particle(Particle(1,'x',40, &my_step_1D_3));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(50000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}

int main() {
    cout<<"Harmonic Oscillator"<<endl;
    //set random seed (use srand(0) if you prefer deterministic behaviour - e.g. for debugging)
    srand (time(NULL));
    classic_harmonic_oscillator();
    quantum_harmonic_oscillator();
    naive_quantum_harmonic_oscillator();
    advanced_naive_quantum_harmonic_oscillator();
    return 0;
}