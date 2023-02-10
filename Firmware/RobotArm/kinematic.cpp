#include "kinematic.hpp"

#include <array>
#include <cstring>

template <typename T1, typename T2, typename Tout>
void prodMatrix(const T1& mat1, const T2& mat2, Tout& resMatrix) {}

void generalTransform(const DhParameters& dh,
                      std::array<TransformMatrix, 6>& robotTransforms,
                      JointAngle& angle) {
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
}

void getGlobalTransformMatrix(const std::array<TransformMatrix, 6>& transformMatrices,
                              globalTransformMatrix& t06) {
    std::array<std::array<float, 4>, 4> t_tmp{transformMatrices[0].t};
    std::array<std::array<float, 4>, 4> intermediateMatrix{};
    for (size_t i = 0; i < 5; ++i) {
        matrixProduct(t_tmp, transformMatrices[i + 1].t, intermediateMatrix);
        t_tmp = intermediateMatrix;
        if (i == 4) {
            t06.tGlobal = t_tmp;
        }
        intermediateMatrix = {};
    }
}
