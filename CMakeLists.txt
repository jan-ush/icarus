set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.15)
project(Icarus VERSION 1.0 LANGUAGES CXX)

# Force C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(implot3d CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCES 
main.cpp
hardware/SensorInterface.cpp
math/CoordinateConversion.cpp
math/UnitConversion.cpp
models/Rocket.cpp
physics/Aerodynamics.cpp
physics/Environment.cpp
simulator/Dynamics.cpp
simulator/State.cpp)

add_executable(icarus ${SOURCES})

target_link_libraries(icarus PRIVATE Eigen3::Eigen imgui::imgui implot::implot implot3d::implot3d OpenGL::GL)
