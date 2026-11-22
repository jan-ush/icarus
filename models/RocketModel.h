#ifndef ROCKET_H
#define ROCKET_H


namespace RocketModel{
    struct Rocket{
        double dryMass;
        double fuelMass;
        double oxidizerMass;
        double fuelConsumption;
        double oxidizerConsumption;
        double singleEngineThrust;
        int numEngines;
    };

    double getMassAfterTime(Rocket rocket, double dryMass, double fuelMass, double elapsedTime, double fuelConsumption, int numEngines);
    double getTotalThrust(Rocket rocket, int activeEngines);
    double getFuelAfterTime(Rocket rocket, double time);
    double getOxidizerAfterTime(Rocket rocket, double time);
}

#endif