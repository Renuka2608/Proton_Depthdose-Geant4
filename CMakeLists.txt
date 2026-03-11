cmake_minimum_required(VERSION 3.16)
project(Proton_DepthDose)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

file(GLOB sources src/*.cc)
file(GLOB headers include/*.hh)

add_executable(Proton_DepthDose main.cc ${sources} ${headers})
target_include_directories(Proton_DepthDose PUBLIC include)
target_link_libraries(Proton_DepthDose ${Geant4_LIBRARIES})

# Auto-copy mac files to output directory (Release) on every build
foreach(_mac run.mac init_vis.mac vis.mac)
    configure_file(
        ${CMAKE_SOURCE_DIR}/${_mac}
        ${CMAKE_CURRENT_BINARY_DIR}/${_mac}
        COPYONLY
    )
endforeach()