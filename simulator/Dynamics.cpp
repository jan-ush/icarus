#include "Dynamics.h"
#include <cmath>
#include <Eigen/Geometry>
#include "../math/UnitConversion.h"

using namespace Eigen;

const double GRAVITY = 9.81;

namespace Dynamics {

double projectileDisplacement(double initialVelocity, double elapsedTime){
    return (0.5)*(-GRAVITY)*(elapsedTime)*(elapsedTime) + (initialVelocity)*(elapsedTime);
}

Vector3d parabolicMotion3D(Vector3d startPosition, double initialVelocity, double launchAngle, double time){
    const double angleRadians = UnitConversion::toRadian(launchAngle);
    const double horizontalVelocity = initialVelocity * std::cos(angleRadians);
    const double verticalVelocity = initialVelocity * std::sin(angleRadians);
    const Vector3d displacement = {
        horizontalVelocity * time,
        0.0,
        projectileDisplacement(verticalVelocity, time)};

    return startPosition + displacement;
}

}