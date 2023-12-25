#include <iostream>
#include <cmath>
#include <vector>

// Laguerre polynomial
double laguerre(double x, int n) {
    double result = 0.0;
    for (int k = 0; k <= n; ++k) {
        result += std::pow(-1.0, k) * std::exp(-x) * std::pow(x, k) / std::tgamma(k + 1);
    }
    return result;
}

// Weight function for Gauss-Laguerre quadrature
double weightFunction(double x) {
    return std::exp(-x);
}

// Function to be integrated
double integrand(double x) {
    return (x * x * std::sin(x * std::sin(x))) / (x * x + 1) * std::exp(-x * x);
}

// Gauss-Laguerre quadrature
double gaussLaguerre(int n) {
    std::vector<double> nodes(n);
    std::vector<double> weights(n);

    // Compute nodes and weights for Gauss-Laguerre quadrature
    for (int i = 0; i < n; ++i) {
        nodes[i] = i + 1;
        weights[i] = laguerre(nodes[i], n - 1) / (nodes[i] * nodes[i]);
    }

    // Perform the quadrature
    double result = 0.0;
    for (int i = 0; i < n; ++i) {
        result += weights[i] * integrand(nodes[i]);
    }

    return result;
}

int main() {
    int numNodes = 100;  // Number of nodes for Gauss-Laguerre quadrature

    double result = gaussLaguerre(numNodes);

    std::cout << "Result: " << result << std::endl;

    return 0;
}