//
// Created by aschethor on 02.11.17.
//

#include "Bead.h"
#include <math.h>

Bead::Bead() {
    x=y=z=0;
}

double inline square(double a){
    return a*a;
}

double Bead::distance_squared(Bead bead) {
    return square(x-bead.x)+square(y-bead.y)+square(z-bead.z);
}

double Bead::distance(Bead bead) {
    return sqrt(distance_squared(bead));
}