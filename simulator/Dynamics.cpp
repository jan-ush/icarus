#include "Dynamics.h"
#include <vector>
#include <Eigen/Geometry>
#include "../math/UnitConversion.h"

using namespace Eigen;

const double GRAVITY = 9.81;

double projectileDisplacement(double initialVelocity, double elapsedTime){
    return (0.5)*(-GRAVITY)*(elapsedTime)*(elapsedTime) + (initialVelocity)*(elapsedTime);
}

Vector3d parabolicMotion3D(Vector3d startPosition, double initialVelocity, Vector3d launchAngle, double time){
    
    //Set startPosition to origin
    double initialVelocity_Z = initialVelocity * cos(UnitConversion::toRadian(launchAngle.z()));
    double initialVelocity_X = initialVelocity * cos(UnitConversion::toRadian(launchAngle.x()));
    double initialVelocity_Y = initialVelocity * cos(UnitConversion::toRadian(launchAngle.y()));

    double position_Z = ((0.5)*(-GRAVITY)*(time)*(time) + (initialVelocity_Z)*(time));
    double position_X = initialVelocity_X * time;
    double position_Y = initialVelocity_Y * time;

    Vector3d displacement = {position_X, position_Y, position_Z};

    return startPosition + displacement;
}