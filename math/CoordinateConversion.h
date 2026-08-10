#ifndef COORDINATE_CONV_H
#define COORDINATE_CONV_H

#include <Eigen/Geometry>

using namespace Eigen;

namespace CoordinateConversion{
    struct LLA {
        double latitude;
        double longitude;
        double altitude;
    };

    struct ECEF {
        double x;
        double y;
        double z;
    };

    struct ENU {
        double east;
        double north;
        double up;
    };

    ECEF gpsToECEF(LLA position);

    ENU ECEFtoENU(ECEF rocketPos, ECEF startPos, LLA startLLA);

    Vector3d toVector(ENU enuCoord);
    Vector3d toVector(ECEF ecefCoord);
    Vector3d toVector(LLA llaCoord);
}

#endif

