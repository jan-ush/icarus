#include <Eigen/Geometry>
#include <vector>

#ifndef STATE_H
#define STATE_H

using namespace Eigen;

namespace State{
    struct currentState
    {
        //STATE VARIABLES
        Vector3d position;
        Vector3d velocity;
        Vector3d acceleration;
        Quaterniond rotation;
        Quaterniond angularVelocity;
        double netMass;
        double fuelMass;
    };
}

#endif