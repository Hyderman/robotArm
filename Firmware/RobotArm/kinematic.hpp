#include <array>
#include <cmath>
#include <numbers>

inline constexpr float PI = std::numbers::pi_v<float>;

inline constexpr void degreeToRad(float& q) {
    q *= PI / 180;
}

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

template <typename T, size_t N>
struct DhParameters {
    std::array<T, N> alpha;
    std::array<T, N> d;
    std::array<T, N> a;
    std::array<T, N> theta;
};

template <typename T>
struct TransformMatrix {
    std::array<std::array<T, 4>, 4> t;
};

template <typename T>
struct GlobalTransformMatrix {
    std::array<std::array<T, 4>, 4> tGlobal;
};

template <typename T, size_t N>
class RobotKinematic {
  public:
    constexpr RobotKinematic(DhParameters<T, N> dh) : dhParams(dh) {}
    constexpr void calculateTransformsMatrices() {
        for (size_t i = 0; i < N; ++i) {
            float cq = cosf(dhParams.theta[i]);
            float sq = sinf(dhParams.theta[i]);
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
    constexpr void calculateGlobalTransformMatrix() {
        t0x = {};
        t0x.tGlobal = transformMatrices[0].t;

        for (size_t i = 0; i < N - 1; ++i) {
            std::array<std::array<T, 4>, 4> t_tmp{};
            matrixProduct(t0x.tGlobal, transformMatrices[i + 1].t, t_tmp);
            t0x.tGlobal = t_tmp;
        }
    }

  private:
    const DhParameters<T, N> dhParams;
    std::array<TransformMatrix<T>, N> transformMatrices;
    GlobalTransformMatrix<T> t0x;
};
