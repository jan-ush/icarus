#include "Environment.h"
#include <vector>
#include <cmath>

namespace Environment {
    double getGravity(){ //Replace with accelerometer data
        return 9.80665;
    }
    double calculateN(double latitude){
        const double a = 6378137.0; //Semumajor Axis of Earth
        const double b = 6356752.3142; //Semiminor Axis of Earth

        const double eccentricity_2 = ((a*a) - (b*b)) / (a*a);

        return a / (std::sqrt(1 - eccentricity_2 * (std::sin(latitude) * std::sin(latitude))));
    }
}