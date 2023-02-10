#include <array>
#include <cmath>
#include <numbers>

inline constexpr float PI = std::numbers::pi_v<float>;

inline constexpr void degreeToRad(float& q) {
    q *= PI / 180;
}

struct DhParameters {
    std::array<float, 6> alpha;
    std::array<float, 6> d;
    std::array<float, 6> a;
    std::array<float, 6> theta;
};

struct TransformMatrix {
    std::array<std::array<float, 4>, 4> t;
};

struct globalTransformMatrix {
    std::array<std::array<float, 4>, 4> tGlobal;
};

struct JointAngle {
    std::array<float, 6> q;
};

void generalTransform(const DhParameters& dh,
                      std::array<TransformMatrix, 6>& robotTransforms,
                      JointAngle& angle);

void getGlobalTransformMatrix(const std::array<TransformMatrix, 6>& transformMatrices,
                              globalTransformMatrix& t0x);

template <typename T, size_t ROWS, size_t COLUMNS>
void matrixProduct(const std::array<std::array<T, COLUMNS>, ROWS>& matrix1,
                   const std::array<std::array<T, COLUMNS>, ROWS>& matrix2,
                   std::array<std::array<T, COLUMNS>, ROWS>& resMatrix) {
    size_t i, j, k;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            for (k = 0; k < COLUMNS; k++) {
                resMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}
