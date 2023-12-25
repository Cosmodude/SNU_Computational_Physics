#include <cstring>
#include <iostream>
#include <cmath>

// used double to get precision
double fsin(double x) {
    double result = 0.0;
    double term = x;
    double epsilon = 1e-14;
    int maxTerms = 100;

    for (int n = 1; n <= maxTerms; n++) {
        result += term;
        term *= -x * x / ((2 * n) * (2 * n + 1));

        if (std::abs(term) < epsilon) {

            if(std::abs(result) < epsilon){
                result = 0;
            }
            break;
        }
    }

    return result;
}

double fcos(double x) {
    double result = 0.0;
    double term = 1.0;
    double epsilon = 1e-14;
    int maxTerms = 100;

    for (int n = 0; n < maxTerms; n++) {
        result += term;
        term *= -x * x / ((2 * n + 1) * (2 * n + 2));

        if (std::abs(term) < epsilon) {
            break;
        }
    }

    return result;
}

double ftan(double x) {
    if(fsin(x) ==0) {return 0;}
    return fsin(x) / fcos(x);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Use: ./trigonometry <angle in radians>" << std::endl;
        return 1;
    }
    double x = std::stof(argv[1]);
    
    std::cout << "sin(" << x << ") = " << fsin(x) << std::endl;
    std::cout << "cos(" << x << ") = " << fcos(x) << std::endl;
    std::cout << "tan(" << x << ") = " << ftan(x) << std::endl;

    return 0;
}
