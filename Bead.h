//
// Created by aschethor on 02.11.17.
//

#ifndef PROJECTQM_ND_2_BEAD_H
#define PROJECTQM_ND_2_BEAD_H

#include <vector>

using namespace std;

class Bead {

public:
    //position of bead and temporary values in case of rejected step
    double x,x_tmp;
    double y,y_tmp;
    double z,z_tmp;

    Bead();
    Bead(void (*step)(Bead* bead,vector<double> randoms));

    //distance squared to bead
    double distance_squared(Bead bead);
    //distance to bead
    double distance(Bead bead);

    //stepping function of bead (not used here, since stepping already done in step()-function of Particle)
    //might be useful in other scenarios
    void (*step)(Bead* bead,vector<double> randoms);

    //copy position values into temporary variables
    void accept();
    //restore position values from temporary variables
    void reject();
};

#endif //PROJECTQM_ND_2_BEAD_H
