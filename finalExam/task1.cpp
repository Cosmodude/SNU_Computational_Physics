#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip> 
#include <vector>
#include <algorithm>

#define MAX_ITER 1e6
#define DEPSILON 1e-20
#define EPSILON 1e-10

double g(double x) {
    return 3 * M_PI * x * x * x / (pow(x, 6) + 1);
}

double h(double x) {
    return 2 * M_PI * x * x * exp(-x * x) / (pow(x, 8) + 1);
}

double f(double x) {
    return cos(g(x) * tan(h(x)));
}

// Define the range [0.3, 1.3]
double lowerBound = 0.4;
double upperBound = 1.3;

// Number of intervals
double numIntervals = 1e6;
// Interval size
double intervalSize = (upperBound - lowerBound) / numIntervals;

double df(double x) {
    double g_prime = (3 * M_PI) * (3 * x * x * (pow(x,6) + 1) - pow(x,3) * 6 * pow(x,5)) / pow(pow(x,6) + 1, 2);
    double h_prime = (4 * M_PI * x ) * (pow(x,10) + 3 * pow(x,8) + pow(x,2) - 1) * exp(- x * x) / pow(pow(x,8) + 1, 2);
    return -sin(g(x) * tan(h(x))) * (g_prime * tan(h(x))) + (g(x) * h_prime / pow(cos(h(x)),2));
}

double newtonMethod(double initialGuess) {
    double x = initialGuess;

    for (int i = 0; i < MAX_ITER; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (std::fabs(dfx) < EPSILON) {
            std::cerr << "Error: Derivative is close to zero. Stopping iterations." << std::endl;
            return NAN;
        }

        double x1 = x - fx / dfx;

        if (std::fabs(x1 - x) < EPSILON) {
            //std::cout << "Root found after " << i + 1 << " iterations." << std::endl;
            return x1;
        }
        if(x1<=1.3){
            x = x1;
        }
        else{x-= intervalSize * 10;}
      
    }

    std::cerr << "Error: Maximum iterations reached." << std::endl;
    return NAN;
}

int main() {
  
    //Step 1: Save Data Points
    std::ofstream dataFile("data.txt");
    for (double x = 0.0; x <= 10.0; x += 0.001) {
        double fx = f(x);
        dataFile << x << " " << fx << std::endl;
    }
    dataFile.close();

    std::vector<double> roots;
    // Find roots in the range [0, +∞], in reality [0.4, 1.3]

     // Find roots in each interval
    for (int i = 0; i < numIntervals; ++i) {
        double initialGuess = lowerBound + i * intervalSize + intervalSize / 2.0;
        double root = newtonMethod(initialGuess);

        if (!std::isnan(root) && root >= lowerBound && root <= upperBound) {
            if (std::find(roots.begin(), roots.end(), root) == roots.end()) {
                roots.push_back(root);
                //std::cout << "Root found: " << std::fixed << root << std::endl;
            }
        }
    }
    // Write roots to a text file
    std::ofstream outputFile("roots.txt");
    std::vector<double> printedRoots;
    if (outputFile.is_open()) {
        outputFile << std::fixed << std::setprecision(11);
        for (const auto &root : roots) {
            double roundedRoot = std::floor(root * std::pow(10, 11)) / std::pow(10, 11);
            if (std::find(printedRoots.begin(), printedRoots.end(), roundedRoot) == printedRoots.end()) {
                outputFile << roundedRoot << std::endl;
                printedRoots.push_back(roundedRoot);
            }
        }
        outputFile.close();
        std::cout << "Roots written to 'roots.txt'." << std::endl;
    } else {
        std::cerr << "Error: Unable to open the output file." << std::endl;
    }

    return 0;
}
