#include "kinematic.hpp"

#include <array>
#include <cstring>

void RobotKinematic::calculateTransformsMatrices() {
    for (size_t i = 0; i < 6; ++i) {
        float cq = cosf(angles.q[i]);
        float sq = sinf(angles.q[i]);
        float calpha = cosf(dhParams.alpha[i]);
        float salpha = sinf(dhParams.alpha[i]);
        float a = dhParams.a[i];
        float d = dhParams.d[i];
        transformMatrices[i].t = {{{cq, -sq, 0, a},
                                   {sq * calpha, cq * calpha, -salpha, -salpha * d},
                                   {sq * salpha, cq * salpha, calpha, calpha * d},
                                   {0, 0, 0, 1}}};
    }
}

void RobotKinematic::calculateGlobalTransformMatrix() {
    t0x = {};
    t0x.tGlobal = transformMatrices[0].t;

    for (size_t i = 0; i < 5; ++i) {
        std::array<std::array<float, 4>, 4> t_tmp{};
        matrixProduct(t0x.tGlobal, transformMatrices[i + 1].t, t_tmp);
        t0x.tGlobal = t_tmp;
    }
}
