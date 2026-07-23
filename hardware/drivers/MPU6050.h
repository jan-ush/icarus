#ifndef MPU_6050_H
#define MPU_6050_H

#include <Eigen/Geometry>

using namespace Eigen;

namespace MPU6050{
    Vector3d getAcceleration();
    Vector3d getAngularVelocity();
    Quaterniond getRotation();
}

#endif