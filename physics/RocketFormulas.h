#pragma once
#include "../models/Rocket.h"
#include "../physics/Environment.h"
#include <cmath>

 namespace RocketFormulas{
    double calculateExhaustVelocity(Rocket::rocketState Rocket){
        double specificImpulse = Rocket.ISP;
        double gravity = Environment::getGravity();

    }

    double deltaV(Rocket::rocketState Rocket);
 }