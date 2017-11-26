//
// Created by aschethor on 02.11.17.
//

#ifndef PROJECTQM_ND_2_BEAD_H
#define PROJECTQM_ND_2_BEAD_H

#include <vector>

using namespace std;

class Bead {

public:
    double x,x_tmp;
    double y,y_tmp;
    double z,z_tmp;

    Bead();//pass step(), make step replaceable?, offer standard function?
    Bead(void (*step)(Bead* bead,vector<double> randoms));
    double distance_squared(Bead bead);
    double distance(Bead bead);
    void (*step)(Bead* bead,vector<double> randoms);
    void accept();
    void reject();
};

#endif //PROJECTQM_ND_2_BEAD_H
