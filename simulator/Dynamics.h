#ifndef DYNAMICS_H
#define DYNAMICS_H
#include <Eigen/Geometry>

using namespace Eigen;

namespace Dynamics{
    double projectileDisplacement(double initialVelocity, double elapsedTime);
    Vector3d parabolicMotion3D(Vector3d startPosition, double initialVelocity, Vector3d launchAngle, double time);
}

#endif