cmake_minimum_required(VERSION 3.16)
project(Proton_DepthDose)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources src/*.cc)
file(GLOB headers include/*.hh)

add_executable(Proton_DepthDose ${sources} ${headers})

target_link_libraries(Proton_DepthDose ${Geant4_LIBRARIES})