#include <RocketFormulas.h>
#include "../models/Rocket.h"
#include "../physics/Environment.h"
#include <cmath>

namespace RocketFormulas{
    double calculateExhaustVelocity(Rocket::rocketState Rocket){
        double specificImpulse = Rocket.ISP;
        double gravity = Environment::getGravity();

        return specificImpulse * gravity;
    }

    double deltaV(Rocket::rocketState Rocket){
        double exhaustVelocity = calculateExhaustVelocity(Rocket);
        double dryMass = Rocket.dryMass;
        double wetMass = Rocket.wetMass;

        return exhaustVelocity * std::log(wetMass/dryMass);
    }
}