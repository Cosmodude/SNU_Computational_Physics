#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

// Function to check if a number is prime
bool isPrime(int number) {
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) return false;
    }
    return true;
}

// Function to find prime numbers less than a given integer
std::set<int> findPrimes(int number) {
    std::set<int> primes;
    for (int i = 2; i < number; i++) {
        if (isPrime(i)) {
            primes.insert(i);
        }
    }
    return primes;
}

// Function to perform prime factorization
std::map<int, int> primeFactorization(int number) {
    std::map<int, int> factors;
    for (int i = 2; i <= number; i++) {
        while (number % i == 0) {
            factors[i]++;
            number /= i;
        }
    }
    return factors;
}

int main() {
    std::ifstream inputFile("input.dat");
    std::ofstream outputFile("output.dat");

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    int x;
    int i = 0;
    while (inputFile >> x) {
        std::set<int> primes = findPrimes(x);
        std::map<int, int> factors = primeFactorization(x);

        outputFile << "S" << i << "p = {";
        for (int prime : primes) {
            outputFile << prime;
            if (prime != *primes.rbegin()) {
                outputFile << ", ";
            }
        }
        outputFile << "}" << std::endl;

        outputFile << "x" << i << " = ";
        for (const auto& factor : factors) {
            outputFile << "(" << factor.first << ", " << factor.second << ")";
            if (factor != *factors.rbegin()) {
                outputFile << " * ";
            }
        }
        outputFile << std::endl;

        i++;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
