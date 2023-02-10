#include "initRobot.h"

#include "kinematic.hpp"

#include <array>

int initInstance(void) {
    const DhParameters dhParams{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
                                {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f},
                                {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f},
                                {100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f}};
    JointAngle joint{90.0f, 45.0f, 180.0f, 45.0f, 270.0f, 90.0f};
    std::array<TransformMatrix, 6> allArmTransform;
    for (float& q : joint.q) {
        degreeToRad(q);
    }
    generalTransform(dhParams, allArmTransform, joint);
    globalTransformMatrix t06{};
    getGlobalTransformMatrix(allArmTransform, t06);
    return 0;
};