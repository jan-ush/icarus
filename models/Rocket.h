#ifndef ROCKET_H
#define ROCKET_H

namespace Rocket{
    struct rocketState{
        const double dryMass;
        const double engineThrust;
        const int numEngines;
        const double ISP;
    };

    double predictMass(double dryMass, double fuelMass, double elapsedTime, double fuelConsumption, int numEngines);
}

#endif