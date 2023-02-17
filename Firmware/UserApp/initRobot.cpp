#include "initRobot.h"

#include "kinematic.hpp"

#include <array>

int initInstance() {
    DhParameters dhParams = {{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
                                   {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
                                   {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f},
                                   {100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f}};
    for (float& q : dhParams.theta) {
        degreeToRad(q);
    }
    RobotKinematic dof6Robot(dhParams);
    dof6Robot.calculateTransformsMatrices();
    dof6Robot.calculateGlobalTransformMatrix();
    return 0;
};