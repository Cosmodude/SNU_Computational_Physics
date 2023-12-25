#include <iostream>
#include <cmath>

double bessel(double x, int s) {
    return (1 / std::tgamma(s + 1)) * std::pow(x / 2, 2 * s) / std::tgamma(s + 1);
}

double function(double x) {
    double result = 0.0;
    for (int s = 0; s < 100; ++s) {
        result += bessel(x, s);
    }
    return std::exp(-8 * x) * result;
}

double trapezoidalRule(double a, double b, int numIntervals, double (*func)(double)) {
    double stepSize = (b - a) / numIntervals;
    double integral = 0.5 * (func(a) + func(b));

    for (int i = 1; i < numIntervals; ++i) {
        integral += func(a + i * stepSize);
    }

    integral *= stepSize;
    return integral;
}

int main() {
    double lowerBound = 0.0;
    double upperBound = 10.0;
    int numIntervals = 100;

    double result = trapezoidalRule(lowerBound, upperBound, numIntervals, function);
    std::cout << "Result of integration using trapezoidal rule: " <<  result << std::endl;

    return 0;
}
