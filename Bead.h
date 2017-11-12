//
// Created by aschethor on 02.11.17.
//

#ifndef PROJECTQM_ND_2_BEAD_H
#define PROJECTQM_ND_2_BEAD_H

#include <vector>

using namespace std;

class Bead {

public:
    double x,y,z;

    Bead();
    double distance_squared(Bead bead);
    double distance(Bead bead);
    void step(vector<double> randoms);
};

#endif //PROJECTQM_ND_2_BEAD_H
