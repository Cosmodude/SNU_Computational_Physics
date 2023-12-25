#include <iostream>
#include <cstring>

float ftoc(float fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

float ctof(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Use: ./temp [-f <temperature in Fahrenheit>] or ./temp [-c <temperature in Celsius>]" << std::endl;
        return 1;
    }

    if (strcmp(argv[1], "-f") == 0) {
        float fahrenheit = std::stof(argv[2]);
        float celsius = ftoc(fahrenheit);
        std::cout << fahrenheit << " Fahrenheit is " << celsius << " Celsius." << std::endl;
    } else if (strcmp(argv[1], "-c") == 0) {
        float celsius = std::stof(argv[2]);
        float fahrenheit = ctof(celsius);
        std::cout << celsius << " Celsius is " << fahrenheit << " Fahrenheit." << std::endl;
    } else {
        std::cout << "Use -f or -c." << std::endl;
        return 1;
    }

    return 0;
}
