#ifndef COORDINATE_CONV_H
#define COORDINATE_CONV_H

#include <Eigen/Geometry>

using namespace Eigen;

namespace CoordinateConversion{
    Vector3d gpsToECEF(double longitude, double latitude, double altitude);
    Vector3d toENU(Vector3d rocketPos_ECEF, Vector3d startPos_ECEF);
}

#endif

