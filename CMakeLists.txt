cmake_minimum_required(VERSION 3.8)
project(ProjectQM_ND_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp System.cpp System.h Particle.cpp Particle.h Bead.cpp Bead.h Constants.h ParticleInterface.h BeadInterface.h)
add_executable(ProjectQM_ND_2 ${SOURCE_FILES})