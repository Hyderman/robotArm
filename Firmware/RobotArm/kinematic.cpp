#include "kinematic.hpp"

#include <array>
#include <cstring>

void RobotKinematic::setTransformsMatrices(const DhParameters& dh, JointAngle& angle) {
    std::array<TransformMatrix, 6> robotTransforms;
    for (size_t i = 0; i < 6; ++i) {
        float cq = cosf(angle.q[i]);
        float sq = sinf(angle.q[i]);
        float calpha = cosf(dh.alpha[i]);
        float salpha = sinf(dh.alpha[i]);
        float a = dh.a[i];
        float d = dh.d[i];
        robotTransforms[i].t = {{{cq, -sq, 0, a},
                                 {sq * calpha, cq * calpha, -salpha, -salpha * d},
                                 {sq * salpha, cq * salpha, calpha, calpha * d},
                                 {0, 0, 0, 1}}};
    }
    transformMatrices_ = robotTransforms;
}

void RobotKinematic::calculateGlobalTransformMatrix() {
    GlobalTransformMatrix t06 = {};
    t06.tGlobal = transformMatrices_[0].t;

    for (size_t i = 0; i < 5; ++i) {
        std::array<std::array<float, 4>, 4> t_tmp{};
        matrixProduct(t06.tGlobal, transformMatrices_[i + 1].t, t_tmp);
        t06.tGlobal = t_tmp;
    }
    t0x_ = t06;
}
