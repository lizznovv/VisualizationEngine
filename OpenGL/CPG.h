#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>

constexpr float PI = 3.14159265358979323846f;

class CPG {
public:
    int n;
    std::vector<float> theta;
    std::vector<float> omega;
    std::vector<std::vector<float>> K;
    std::vector<std::vector<float>> phi;

    float A = 0.3f;

    CPG(int n) : n(n) {
        theta.resize(n, 0.0f);
        omega.resize(n, 2 * PI * 1.5f);

        K.resize(n, std::vector<float>(n, 0.0f));
        phi.resize(n, std::vector<float>(n, 0.0f));

        for (int i = 0; i < n - 1; i++) {
            K[i][i + 1] = 5;
            K[i + 1][i] = 5;

            phi[i][i + 1] = 0.4f;
            phi[i + 1][i] = -0.4f;
        }
    }

    void step(float dt) {
        std::vector<float> dtheta(n, 0.0f);

        for (int i = 0; i < n; i++) {
            dtheta[i] = omega[i];

            for (int j = 0; j < n; j++) {
                dtheta[i] += K[i][j] * sin(
                    theta[j] - theta[i] - phi[i][j]
                );
            }
        }

        for (int i = 0; i < n; i++) {
            theta[i] += dt * dtheta[i];
        }
    }

    std::vector<float> getAngles() {
        std::vector<float> angles(n);
        for (int i = 0; i < n; i++) {
            angles[i] = A * cos(theta[i]);
        }
        return angles;
    }
};