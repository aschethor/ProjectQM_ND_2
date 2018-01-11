cmake_minimum_required(VERSION 3.8)
project(ProjectQM_ND_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Utils.h System.cpp System.h Particle.cpp Particle.h Bead.cpp Bead.h)
add_executable(ProjectQM_ND_2 Examples/main.cpp ${SOURCE_FILES})
add_executable(HarmonicOscillator1D Examples/HarmonicOscillator1D.cpp ${SOURCE_FILES})
add_executable(Morse3D Examples/Morse3D.cpp ${SOURCE_FILES})
add_executable(ProductInteraction Examples/ProductInteraction.cpp ${SOURCE_FILES})
add_executable(Presentation_HarmonicPotential Presentation/HarmonicPotential.cpp ${SOURCE_FILES})
add_executable(Presentation_DoubleWellPotential Presentation/DoubleWellPotential.cpp ${SOURCE_FILES})