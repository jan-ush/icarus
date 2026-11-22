#include "RocketModel.h"
#include <vector>


namespace RocketModel {
    double getMassAfterTime(Rocket rocket, double time){
        double remainingFuel = std::max(0.0, (rocket.fuelMass - (rocket.fuelConsumption * rocket.numEngines * time)));
        return rocket.dryMass + remainingFuel;
    }

    double getTotalThrust(Rocket rocket, int activeEngines) {
        return rocket.singleEngineThrust * activeEngines;
    }

    double getFuelAfterTime(Rocket rocket, double time) {
        return rocket.fuelMass - rocket.fuelConsumption * rocket.numEngines * time;
    }

    double getOxidizerAfterTime(Rocket rocket, double time) {
        return rocket.oxidizerMass - rocket.oxidizerConsumption * rocket.numEngines * time;
    }
}

