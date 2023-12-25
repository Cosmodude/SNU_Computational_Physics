
#include <iostream>
#include <fstream>
#include <cmath>

double f(double x) {
	return sin(10. * (pow(x, 2) + 1.) / (pow(x, 4) + pow(x, 2) + 1.) * exp(-(1. / 2) * pow(x, 2)));
}


double f_prime(double x) {
	return -(10. * x * (1. + 6. * pow(x, 2) + 4. * pow(x, 4) + pow(x, 6))) / pow((1. + pow(x, 2) + pow(x, 4)), 2) * cos(10. * (pow(x, 2) + 1) / (pow(x, 4) + pow(x, 2) + 1.) * exp(-(1. / 2) * pow(x, 2))) * exp(-(1. / 2) * pow(x, 2));
}

double newtons_method(
    double x0,                                  // The initial guess
    double tolerance,                           // Stop when iterations change by less than this
    double a1,                                  // Right side of interval
    double a2,                                  // Left side of interval
    int max_iterations                        // The maximum number of iterations to compute
    ) {
    double y = 0;
    double y_prime = 0;
    double x1 = 0;

    for (int i = 0; i < max_iterations; i++) {
        y = f(x0);
        y_prime = f_prime(x0);

        if (y_prime == 0) {
            return NAN;
        }

        x1 = x0 - y/y_prime;

        if (abs(x1 - x0) <= tolerance) {
            if (not((a1 < x1) and (x1 < a2))) {
                return NAN;
            }
            return x1;
        }

        x0 = x1;
        
    }

    return NAN;
}



int main()
{
    double root1 = 0;
    double root2 = 0;
    double root3 = 0;


    /*std::ofstream file;
    file.open("graph.txt");
    for (double i = 0; i <= 5; i += 0.01) {
        file << i << "\t" << f(i) << "\n";
    }
    file.close();*/

    root1 = newtons_method(0.3, 1e-11, 0, 5, 1000000);
    root2 = newtons_method(0.7, 1e-11, 0, 5, 1000000);
    root3 = newtons_method(1, 1e-11, 0, 5, 1000000);
    std::cout << "first root is " << root1 << "\n";
    std::cout << "second root is " << root2 << "\n" ; 
    std::cout << "third root is " << root3 << "\n";
}
