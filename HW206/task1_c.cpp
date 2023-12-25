#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Define the integrand function
double integrand(double x) {
    return (x * x * std::sin(x * std::sin(x))) / (x * x + 1) * std::exp(-x * x);
}

// Define the weight function
double weightFunction(double x) {
    return 1.0 / (x * x + 1) * std::exp(-x * x);
}

// Metropolis algorithm for numerical integration
double metropolisIntegration(int numSamples) {
    std::srand(static_cast<unsigned>(std::time(0))); // Seed for random number generation

    double integralSum = 0.0;
    double x = 0.0;

    for (int i = 0; i < numSamples; ++i) {
        // Propose a new sample using a random step between 0 and 0.1
        double xNew = x + 0.000015 * (std::rand() / static_cast<double>(RAND_MAX));

        // Metropolis acceptance criterion
        double acceptanceRatio = weightFunction(xNew) / weightFunction(x);
        if (std::rand() / static_cast<double>(RAND_MAX) < acceptanceRatio) {
            x = xNew;
        }

        // Accumulate the integrand value
        integralSum += integrand(x);
    }

    // Normalize by the number of samples
    return integralSum / numSamples;
}

int main() {
    int numSamples = 1000000; // Adjust the number of samples as needed

    double result = metropolisIntegration(numSamples);

    std::cout << "Result: " << result << std::endl;

    return 0;
}
