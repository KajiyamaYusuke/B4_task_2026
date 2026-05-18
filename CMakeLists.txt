cmake_minimum_required(VERSION 3.10)

project(kadai_all C CXX)

find_package(Eigen3 REQUIRED NO_MODULE)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB CPP_SOURCES "*.cpp")

foreach(src ${CPP_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} Eigen3::Eigen m)
endforeach()

file(GLOB C_SOURCES "*.c")

foreach(src ${C_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} m)
endforeach()