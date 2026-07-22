#include "CoordinateConversion.h"

#include <iostream>
#include <Eigen/Geometry>
#include "UnitConversion.h"
#include "../physics/Radius.h"

using namespace std;
using namespace Eigen;
using namespace UnitConversion;

const double PI = 3.14159265358979323846;

Matrix3d rotation;



Vector3d gpsToECEF(double longitude, double latitude, double altitude){
    double long_Rad = toRadian(longitude);
    double lat_Rad = toRadian(latitude);
    double RADIUS = Radius::caclulateRadius(latitude);

    double x = (RADIUS+altitude) * cos(lat_Rad) * cos(long_Rad);
    double y = (RADIUS+altitude) * cos(lat_Rad) * sin(long_Rad);
    double z = (RADIUS+altitude) * sin(lat_Rad);

    return Vector3d (x, y, z);
}

Vector3d toENU(Vector3d rocketPos_ECEF, Vector3d startPos_ECEF, Vector3d startPos_LLA){
    double refLong = startPos_LLA.x();
    double refLat = startPos_LLA.y();

    rotation << 
    -sin(refLong),              cos(refLong),             0,
    -sin(refLat)*cos(refLong),    -sin(refLat)*sin(refLong),    cos(refLat),
    cos(refLat)*cos(refLong),     cos(refLat)*sin(refLong),    sin(refLat);

    Vector3d delta_ECEF = rocketPos_ECEF - startPos_ECEF;
    Vector3d position_ENU = rotation * delta_ECEF;

    return position_ENU;
}
