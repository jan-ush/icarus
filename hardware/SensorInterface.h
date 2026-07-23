#ifndef SENSOR_INT_H
#define SENSOR_INT_H

#include <Eigen/Geometry>

using namespace Eigen;

namespace SensorInterface{
    Vector3d getAcceleration();
    Vector3d getAngularVelocity();
    Quaterniond getRotation();
    
    double getAltitude();
    double getClimbRate();
    double getTemperature();
}

#endif