#include <iostream>
#include <math.h>
#include <time.h>
#include "Particle.h"
#include "System.h"
#include "Constants.h"
#include <fstream>

using namespace std;

ofstream output_file;

void observable(System& system){
    for(int i=0;i<system.particles[0].beads.size();i++){
        output_file<<""<<system.particles[0].beads[i].x<<", "
                       <<system.particles[0].beads[i].y<<", "
                       <<system.particles[0].beads[i].z<<endl;
    }
}

double morse_potential(double distance){
    double D_e = 1;   // dissociation energy
    double R_e = 0.5; // nuclear distance to minimum potential energy
    double a = 1;     // potential width
    return D_e*(1-exp(a*(R_e-distance)))*(1-exp(a*(R_e-distance)));
}

double external_potential(Bead bead){
    double distance = 1; //distance of O-atoms to center
    double d1 = sqrt((bead.x-distance)*(bead.x-distance)+bead.y*bead.y+bead.z*bead.z);
    double d2 = sqrt((bead.x+distance)*(bead.x+distance)+bead.y*bead.y+bead.z*bead.z);
    return morse_potential(d1)+morse_potential(d2);
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

void classic_morse(){
    cout<<"classical... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\morse_3d_cl.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.add_particle(Particle(1,'x',1));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(500000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}

void quantum_morse(){
    cout<<"quantum mode... ";
    output_file.open("C:\\Users\\NiWa\\Documents\\MATLAB\\Project CQM\\morse_3d_qm.csv");
    System system(&my_calc_internal_term,&my_calc_external_term);
    system.add_particle(Particle(1,'x',40));
    system.monte_carlo(1000);
    system.add_observable(&observable);
    system.monte_carlo(50000);
    cout<<"done. accepted vs rejected samples: "<<system.n_accepted<<" / "<<system.n_rejected<<endl;
    output_file.close();
}

int main() {
    cout<<"3D Morse Potential"<<endl;
    srand (time(NULL));
    classic_morse();
    quantum_morse();
    return 0;
}