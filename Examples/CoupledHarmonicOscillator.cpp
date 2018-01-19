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
    for(int i=0;i<system.particles[0].beads.size();i++){
        output_file<<""<<system.particles[0].beads[i].x<<", "<<system.particles[1].beads[i].x<<endl;//assuming same number of beads
    }
}

double external_potential(Bead bead){
    double k = 1;
    return k/2*bead.x*bead.x;
}

double my_calc_external_term(Particle& particle){
    int n = particle.beads.size();
    double term = 0;
    for(int i=0;i<n;i++){
        term += external_potential(particle.beads[i]);
    }
    return particle.mass*term/n;
}

// this function calculates the interaction potential between 2 particles
double my_calc_internal_term(Particle& particle1,Particle& particle2){
    double kappa=1;
    int n1 = particle1.beads.size();
    int n2 = particle2.beads.size();
    if(n1==n2){
        double term = 0;
        for(int i=0;i<n1;i++){
            term += (particle1.beads[i].x-particle2.beads[i].x)*(particle1.beads[i].x-particle2.beads[i].x);
        }
        return kappa/2*term/n1;
    }
    return 0;
}

void my_step_1D(Particle* particle,vector<double> randoms){
    if(randoms.size()==0){
        double alpha = 0.1;
        double x = (rand_u()*2-1)*alpha;

        int mode = get_mode(particle->beads.size()/2);

        double phase = rand_u()*M_PI/2;
        for(int i=0;i<particle->beads.size();i++){
            double factor = sin(i*mode*2*M_PI/particle->beads.size()+phase);
            particle->beads[i].x += factor*x;
        }
    }
}

void my_step_1D_adv_naive(Particle *particle, vector<double> randoms){
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

void classic_coupled_harmonic_oscillator_adv_naive(){
    cout<<"classical advanced naive... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\coupled_harmonic_oscillator_k1_cl_adv_naive.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.set_T(0.1);
    system.add_particle(Particle(1,'x',1, &my_step_1D_adv_naive));
    system.add_particle(Particle(1,'x',1, &my_step_1D_adv_naive));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(500000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}
void classic_coupled_harmonic_oscillator(){
    cout<<"classical... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\coupled_harmonic_oscillator_k1_cl.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.set_T(0.1);
    system.add_particle(Particle(1,'x',1,&my_step_1D));
    system.add_particle(Particle(1,'x',1,&my_step_1D));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(500000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}

void quantum_coupled_harmonic_oscillator_adv_naive(){
    cout<<"quantum advance naive... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\coupled_harmonic_oscillator_k1_qm_adv_naive.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.set_T(0.1);
    system.add_particle(Particle(1,'x',40, &my_step_1D_adv_naive));
    system.add_particle(Particle(1,'x',40, &my_step_1D_adv_naive));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(500000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}

void quantum_coupled_harmonic_oscillator(){
    cout<<"quantum... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\coupled_harmonic_oscillator_k1_qm.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.set_T(0.1);
    system.add_particle(Particle(1,'x',40,&my_step_1D));
    system.add_particle(Particle(1,'x',40,&my_step_1D));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(500000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}


int main() {
    cout<<"Coupled Harmonic Oscillator"<<endl;
    srand (time(NULL));
    classic_coupled_harmonic_oscillator_adv_naive();
    classic_coupled_harmonic_oscillator();
    quantum_coupled_harmonic_oscillator_adv_naive();
    quantum_coupled_harmonic_oscillator();
    return 0;
}