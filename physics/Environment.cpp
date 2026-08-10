#include "Environment.h"
#include <math.h>
#include <vector>

namespace Environment {
    const double a = 6378137.0; //Semumajor Axis of Earth
    const double b = 6356752.3142; //Semiminor Axis of Earth

    const double eccentricity_2 = ((a*a) - (b*b)) / (a*a);

    double calculateN(double latitude){
        return a / (sqrt (1 - eccentricity_2 * ( sin(latitude) * sin(latitude))));
    }

    double getEccentricity(){return eccentricity_2;}
}
