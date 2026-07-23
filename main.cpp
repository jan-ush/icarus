#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Geometry>
#include <numbers>
#define _USE_MATH_DEFINES
#include <cmath>

#include "math/CoordinateConversion.h"
#include "math/UnitConversion.h"

#include "models/Rocket.h"

using namespace std;
using namespace Eigen;

using namespace CoordinateConversion;
using namespace UnitConversion;

const double RADIUS = 6371000;

int main(){
    //Engine Spec (HARDCODED BASED ON ROCKET CONFIG, SAMPLE VALUES BASED ON FALCON 9)
    const double engine_thrust = 845.0; //kN
    const int num_engines = 9;

    const double dryMass = 26200.0; // Kg
    const double fuelMass = 362600.0; // Kg of liquid fuel
    const double oxidizerMass = 155800.0; // Kg of oxidizer

    const double fuelRate = 194.0; // Kg/s 
    const double oxiRate = 79.0;  // Kg/s

    //Launchpad coordinates
    const double launch_long = -80.5772;
    const double launch_lat = 28.5619;
    const double launch_alt = 3.0;

    //Sensor Data
    double altitude;
    double longitude;
    double latitude;

    //Convert Sensor Data to Vectors
    Vector3d ECEF_rocketPosition = gpsToECEF(longitude, latitude, altitude);
    Vector3d ECEF_startPosition = gpsToECEF(launch_long, launch_lat, launch_alt);
    Vector3d velocity;
    Vector3d acceleration;

    Quaterniond rotation;
    Quaterniond angularVelocity;

    return 0;
}