#include <iostream>
#include <cstring>

// Function to convert Fahrenheit to Celsius
float ftoc(float fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

// Function to convert Celsius to Fahrenheit
float ctof(float celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Use: ./temp [-f <temperature in Fahrenheit>] or ./temp [-c <temperature in Celsius>]" << std::endl;
        return 1;
    }

    float (*convert_tempature)(float);

    if (strcmp(argv[1], "-f") == 0) {
        convert_tempature = ftoc;  
    } else if (strcmp(argv[1], "-c") == 0) {
        convert_tempature = ctof; 
    } else {
        std::cout << "Use -f or -c." << std::endl;
        return 1;
    }

    float input_temp = std::stof(argv[2]);
    float converted_temp = convert_tempature(input_temp);

    // Display the result
    std::cout << argv[2] << " degrees " << (strcmp(argv[1], "-f") == 0 ? "Fahrenheit" : "Celsius") << " is " << converted_temp << " degrees " << (strcmp(argv[1], "-f") == 0 ? "Celsius" : "Fahrenheit") << "." << std::endl;

    return 0;
}