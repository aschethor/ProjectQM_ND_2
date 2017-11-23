//
// Created by NiWa on 12.11.2017.
//

#ifndef PROJECTQM_ND_2_PARTICLEINTERFACE_H
#define PROJECTQM_ND_2_PARTICLEINTERFACE_H

#include "BeadInterface.h"
#include <vector>

class ParticleInterface{

public:
    virtual int getChainLength()=0;
    virtual BeadInterface* getBead(int numerator,int denominator)=0;
    double kinetic_term();
    virtual double potential_term()=0;
    virtual double cross_potential_term(ParticleInterface particle)=0;
    virtual void step(std::vector<double> randoms)=0;
};

#endif //PROJECTQM_ND_2_PARTICLEINTERFACE_H
