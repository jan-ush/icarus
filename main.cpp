
#include <Eigen/Geometry>
#include <iostream>

#define _USE_MATH_DEFINES


#include "math/CoordinateConversion.h"
#include "math/UnitConversion.h"

#include "physics/Environment.h"

#include "models/Rocket.h"

using namespace std;
using namespace Eigen;

using namespace CoordinateConversion;
using namespace UnitConversion;
using namespace Environment;

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
    LLA launchpad = {
        28.5619,
        -80.5772,
        3.0
    };

    //Sensor Data
    LLA currentPos = {
        launchpad.latitude + 0.00270,
        launchpad.longitude  + 0.00307,
        1000.0
    };

    //Convert Sensor Data to Vectors
    ECEF ECEF_rocketPosition = gpsToECEF(currentPos);
    ECEF ECEF_startPosition = gpsToECEF(launchpad);
    Vector3d velocity;
    Vector3d acceleration;

    Quaterniond rotation;
    Quaterniond angularVelocity;

    ENU TEST_ENU = ECEFtoENU(ECEF_rocketPosition, ECEF_startPosition, launchpad);

    string output = "Rocket Position in ENU: " + to_string(TEST_ENU.east) + ", " + to_string(TEST_ENU.north) + ", " + to_string(TEST_ENU.up);

    cout << output;

    return 0;
}