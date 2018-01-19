#include <iostream>
#include <math.h>
#include <time.h>
#include "../System.h"
#include "../Particle.h"
#include "../Utils.h"
#include <fstream>

using namespace std;

ofstream output_file;

void observable(System& system){
    for(int i=0;i<system.particles[0].beads.size();i++){
        output_file<<""<<system.particles[0].beads[i].x<<endl;
    }
}

double external_potential(Bead bead){
    double w = 1;
    return w*w*(bead.x-1)*(bead.x-1)*(bead.x+1)*(bead.x+1);
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

/*
 * mode-stepping in 1 dimension
 */
void my_step_1D(Particle* particle,vector<double> randoms){
    if(randoms.size()==0){
        double alpha = 1;
        double x = (rand_u()*2-1)*alpha;
        // excite "modes" of bead-ring
        // int mode = min(-(int)log2(rand_u()),particle->beads.size()/2);
        int mode = get_mode(particle->beads.size()/2);
        // cout<<" excited mode: "<<mode<<" x: "<<x<<endl;
        double phase = rand_u()*M_PI/2;
        for(int i=0;i<particle->beads.size();i++){
            double factor = sin(i*mode*2*M_PI/particle->beads.size()+phase);
            particle->beads[i].x += factor*x;
        }
    }
}

void quantum_double_well(double temperature, int n_beads){
    cout<<"Simulation: Temperature = "<<temperature<<"; Number of Beads = "<<n_beads<<endl;
    string filename = "C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\data\\presentation\\double_well_qm_T_"
                      + to_string(temperature)+"_N_"+to_string(n_beads)+".csv";
    output_file.open(filename);
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.set_T(temperature);
    system.add_particle(Particle(1,'x',n_beads,&my_step_1D));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(500000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}

//TODO: Bug: sometimes program execution seems to stop without any reason / error message (even during printing)

int main() {
    cout<<"Harmonic Oscillator"<<endl;
    srand (0);//(time(NULL));
    double temperatures[] = {0.1,1};//{0.1,1};
    int n_beads[] = {1,2,4,8,16,32,64};
    for(double t:temperatures){
        for(int n:n_beads){
            quantum_double_well(t, n);
        }
    }
    return 0;
}