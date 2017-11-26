//
// Created by aschethor on 02.11.17.
//

#include "Bead.h"
#include <math.h>
#include <iostream>

using namespace std;

void _step(Bead* bead,vector<double> randoms) {
    // cout<<"Bead step";
    if(randoms.size()==3){
        bead->x += randoms[0];
        bead->y += randoms[1];
        bead->z += randoms[2];
        // cout<<" x: "<<bead->x<<endl;
    }
}

Bead::Bead() {
    x = y = z = 0;
    x_tmp = y_tmp = z_tmp = 0;
    this->step = _step;
}

Bead::Bead(void (*step)(Bead *bead, vector<double> randoms)) {
    x = y = z = 0;
    x_tmp = y_tmp = z_tmp = 0;
    this->step = step;
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

void Bead::accept() {
    x_tmp = x;
    y_tmp = y;
    z_tmp = z;
}

void Bead::reject() {
    x = x_tmp;
    y = y_tmp;
    z = z_tmp;
}