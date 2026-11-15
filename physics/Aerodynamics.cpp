#include "Aerodynamics.h"

double Aerodynamics::calculateDrag(double velocity, double airDensity, double dragCoefficient, double referenceArea){
    return 0.5 * airDensity * velocity * velocity * dragCoefficient * referenceArea;
}