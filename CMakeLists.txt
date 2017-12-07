cmake_minimum_required(VERSION 3.8)
project(ProjectQM_ND_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Utils.h System.cpp System.h Particle.cpp Particle.h Bead.cpp Bead.h ParticleInterface.h BeadInterface.h)
add_executable(ProjectQM_ND_2 main.cpp ${SOURCE_FILES})
add_executable(HarmonicOscillator1D HarmonicOscillator1D.cpp ${SOURCE_FILES})
add_executable(Morse3D Morse3D.cpp ${SOURCE_FILES})
add_executable(ProductInteraction ProductInteraction.cpp ${SOURCE_FILES})