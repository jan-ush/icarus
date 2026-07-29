set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.15)
project(Icarus VERSION 1.0 LANGUAGES CXX)

# Force C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Locate the Eigen package automatically via Homebrew/System paths
find_package(Eigen3 5.0.1 REQUIRED)

# 2. Define your executable and its source files
# Recursively find every .cpp file in the project directory and its subfolders
set(SOURCES 
main.cpp
hardware/SensorInterface.cpp
math/CoordinateConversion.cpp
math/UnitConversion.cpp
models/Rocket.cpp
physics/Aerodynamics.cpp
physics/Environment.cpp
physics/Propulsion.cpp
simulator/Dynamics.cpp
simulator/State.cpp)

add_executable(icarus ${SOURCES})

# 3. Dynamically link Eigen's include headers to your target
target_link_libraries(icarus PRIVATE Eigen3::Eigen)
