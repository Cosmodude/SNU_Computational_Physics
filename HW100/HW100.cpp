#include <iostream>
#include <iomanip> 

double converterCF(double celsius) {  // celsius To Fahrenheit
    return (celsius * 9.0/5.0) + 32.0;
}

int main() {

    for (int celsius = 0; celsius <= 300; celsius += 20) {
        double fahr = converterCF(celsius);
        std::cout << std::setw(10) << "Celsius" << std::setw(15) << "Fahrenheit" << std::endl;
        std::cout << std::setw(10) << "-------" << std::setw(15) << "----------" << std::endl;
        
        std::cout << std::setw(10) << celsius << std::setw(15) << std::fixed << std::setprecision(2) << fahr<< std::endl;
        std::cout << std::endl;
    }
    return 0;
}


