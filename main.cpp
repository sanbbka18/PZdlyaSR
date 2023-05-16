#include <iostream>
#include <cmath>
#include <vector>
#include <omp.h>

double calculateDistanceP(const std::vector<double>& X, const std::vector<double>& Y, int p) {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < X.size(); i++) {
        sum += std::pow(std::abs(X[i] - Y[i]), p);
    }
    sum = std::pow(sum, 1.0 / p);
    return sum;
}

double calculateDistanceInfinity(const std::vector<double>& X, const std::vector<double>& Y) {
    double maxDiff = 0.0;
    #pragma omp parallel for reduction(max:maxDiff)
    for (int i = 0; i < X.size(); i++) {
        double diff = std::abs(X[i] - Y[i]);
        if (diff > maxDiff) {
            maxDiff = diff;
        }
    }
    return maxDiff;
}

int main() {
    std::vector<double> X = {1.0, 2.0, 3.0};
    std::vector<double> Y = {4.0, 5.0, 6.0};

    int p = 2;

    double distanceP = calculateDistanceP(X, Y, p);
    double distanceInfinity = calculateDistanceInfinity(X, Y);

    std::cout << "Distance (p = " << p << "): " << distanceP << std::endl;
    std::cout << "Distance (Infinity): " << distanceInfinity << std::endl;

    return 0;
}
