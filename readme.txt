11.01.2018 by Nils Wandel
Semester project: "Advanced Monte Carlo Methods for Quantum Thermal Averages"
This repository contains C++ and Matlab code to calculate quantum thermal averages and free energies using feynman
path integrals and markov chain monte carlo techniques.
It is split into 2 parts:
1.) C++:
    the C++ code is a flexible way to sample thermal averages of physical systems with an arbitrary number of particles
    using feynman path integrals. The statistics can follow a hamiltonian containing external potential terms as well as
    interaction terms between 2 particles.
    It is split into 3 main classes: System, Particle and Bead.
    System: The system class contains all the information about the system, such as temperature, observables, internal
    and external potential terms and of course also the particles of the system. Sampling can be done by calling the
    monte_carlo(int n_steps) method, which then performs n_steps monte carlo steps and stores the results via the
    specified observable - functions.
    Particle: the particle class contains information about the particle, such as mass, element, number of beads and the
    beats themselves. It allows to exchange the monte-carlo stepping technique by a custom one (for example if the
    system is only 1 dimensional).
    Bead: helper class containing the x,y,z position of a bead.
    If you want to dive deeper into the code, I'd recommend to run the examples (in the Examples folder). They show you
    how to use all the functionality mentioned above (like specifying the hamiltonian in terms of interaction terms and
    external potentials, how to create observables or how to exchange the stepping technique).
2.) Matlab:
    This repository also contains some Matlab files in order to analyse the results from the monte carlo sampling. In
    particular they provide a way to compute the quantum thermal averages and free energy surfaces of some of the
    example problems.