#include "CoordinateConversion.h"

#include <iostream>
#include <Eigen/Geometry>
#include "UnitConversion.h"
#include "../physics/Environment.h"

using namespace std;
using namespace Eigen;
using namespace UnitConversion;
using namespace Environment;

const double PI = 3.14159265358979323846;

/*
ECEF 
- Earth Centred, Earth Fixed Coordinates 
- Position relative to the centre of the Earth
- Vector3 (x, y, z)

--

ENU
 - East, North, Up
 - Position relative to a fixed reference point (like a launch pad)
 - Vector3 (East, North, Up)
 - Opposite direction (West, South, Down) represented as negative numbers

*/

Matrix3d rotation;

namespace CoordinateConversion {
 Vector3d toVector(ECEF ecefCoord) {
  return Vector3d(ecefCoord.x, ecefCoord.y, ecefCoord.z);
 }

 Vector3d toVector(LLA llaCoord) {
  return Vector3d(llaCoord.latitude, llaCoord.longitude, llaCoord.altitude);
 }

 Vector3d toVector(ENU enuCoord) {
  return Vector3d(enuCoord.east, enuCoord.north, enuCoord.up);
 }

 ECEF gpsToECEF(LLA position){

  double latitude = position.latitude;
  double longitude = position.longitude;
  double altitude = position.altitude;

  double long_Rad = toRadian(longitude);
  double lat_Rad = toRadian(latitude);
  double N = calculateN(toRadian(latitude));

  double x = (N+altitude) * cos(lat_Rad) * cos(long_Rad);
  double y = (N+altitude) * cos(lat_Rad) * sin(long_Rad);
  double z = (N*(1-getEccentricity())+altitude) * sin(lat_Rad);

  return ECEF{x, y, z};
 }

 ENU ECEFtoENU(ECEF rocketPos_ECEF, ECEF startPos_ECEF, LLA StartPos){
  double refLong = toRadian(StartPos.longitude);
  double refLat = toRadian(StartPos.latitude);

  rotation <<
  -sin(refLong),              cos(refLong),             0,
  -sin(refLat)*cos(refLong),    -sin(refLat)*sin(refLong),    cos(refLat),
  cos(refLat)*cos(refLong),     cos(refLat)*sin(refLong),    sin(refLat);

  Vector3d delta_ECEF = toVector(rocketPos_ECEF) - toVector(startPos_ECEF);
  Vector3d position_ENU = rotation * delta_ECEF;

  return ENU{position_ENU.x(), position_ENU.y(), position_ENU.z()};
 }
}



