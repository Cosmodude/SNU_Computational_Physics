#include <iostream>
#include <vector>
#include <iomanip>

// Function to multiply a big integer by an integer
void multiply(std::vector<int>& result, int num) {
    int carry = 0;
    for (int i = 0; i < result.size(); i++) {
        int product = result[i] * num + carry;
        result[i] = product % 100; // Each element represents two digits
        carry = product / 100;
    }
    while (carry) {
        result.push_back(carry % 100);
        carry /= 100;
    }
}

// Function to calculate factorial and store it in an array
void calculateFactorial(int x, std::vector<int>& result) {
    result.clear();
    result.push_back(1); // Initialize with 1

    for (int i = 2; i <= x; i++) {
        multiply(result, i);
    }
}

int main() {
    int x;
    std::cout << "Enter an integer x: ";
    std::cin >> x;

    std::vector<int> result;
    calculateFactorial(x, result);

    // Print the full precision result
    std::cout << x << "! = ";
    for (int i = result.size() - 1; i >= 0; i--) {
        if (i == result.size() - 1) {
            std::cout << result[i];
        } else {
            // Print leading zeros if present
            std::cout << std::setw(2) << std::setfill('0') << result[i];
        }
    }
    std::cout << std::endl;

    // Convert the result to a double precision number and print
    double factorialDouble = 0.0;
    for (int i = result.size() - 1; i >= 0; i--) {
        factorialDouble = factorialDouble * 100 + result[i];
    }
    std::cout << "Factorial as a double precision number: " << factorialDouble << std::endl;

    return 0;
}
