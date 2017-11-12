#include <iostream>
#include "Particle.h"
#include "System.h"

using namespace std;

double my_potential(Bead bead){
    double w=2;
    return w*(bead.x*bead.x+bead.y*bead.y+bead.z*bead.z);
}


class A{
public:
    virtual void test(){
        cout<<"testA"<<endl;
    }
    virtual void blubb()=0;
};

class B:public A{
public:
    void test(){
        cout<<"testB"<<endl;
    }
    void blubb(){
        cout<<"blubbB"<<endl;
    }
};

void testSystem1(){
    Particle testParticle(1,4,&my_potential);
    testParticle.beads[0].x = 1;
    cout << "distance squared: " << testParticle.beads[0].distance_squared(testParticle.beads[1]) << endl;
    cout << "kinetic term: " << testParticle.kinetic_term() << endl;
    cout << "potential term: " << testParticle.external_potential(testParticle.beads[0]) << endl;
    System testSystem;
    testSystem.add_particle(testParticle);
    testSystem.add_particle(Particle(1,4,&my_potential));
    cout << "System probability: " << testSystem.probability() << endl;
    testSystem.particles[0].step(vector<double>());
    testSystem.particles[1].step(vector<double>());
}
int main() {
    vector<A*> as;
    B b;
    b.blubb();
    b.test();
    as.push_back(&b);
    as[0]->blubb();
    as[0]->test();
    //as.push_back(new A());
    //as[1]->test();
    return 0;
}