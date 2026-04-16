cmake_minimum_required(VERSION 3.10)

project(kadai_all CXX)

find_package(Eigen3 REQUIRED NO_MODULE)

file(GLOB SOURCES "*.cpp")

foreach(src ${SOURCES})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} Eigen3::Eigen m)
endforeach()