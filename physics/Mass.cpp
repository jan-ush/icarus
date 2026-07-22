#include "Mass.h"
#include <vector>

double calculateMass(double dryMass,
                     double fuelMass, 
                     double elapsedTime, 
                     double fuelConsumption, 
                     int numEngines){

    double remainingFuel = std::max(0.0, (fuelMass - (fuelConsumption * numEngines * elapsedTime)));
    return dryMass + remainingFuel;
}

