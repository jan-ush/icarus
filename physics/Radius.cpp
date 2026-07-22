#include "Radius.h"
#include <vector>

double calculateRadius(double latitude){
    const double a = 6378137.0; //Semumajor Axis of Earth
    const double b = 6356752.3142; //Semiminor Axis of Earth
    
    const double eccentricity_2 = ((a*a) - (b*b)) / (a*a);

    return a / (sqrt (1 - eccentricity_2 * ( sin(latitude) * sin(latitude))));
}
