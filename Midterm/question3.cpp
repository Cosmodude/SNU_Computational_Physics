#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

int main() {
    std::ifstream inputFile("data.2023-10-27");
    std::ofstream outputFile("stat.out");

    if (!inputFile || !outputFile) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    double x, fx;
    std::vector<std::vector<double>> data; // Store data as (x, f(x)) pairs

    while (inputFile >> x >> fx) {
        data.push_back({x, fx});
    }

    int dataSize = data.size();
    
    // Calculate average and error for each x value
    for (double xPos = 0; xPos <= 6; xPos += 0.1) {
        double sum = 0.0;
        int count = 0;
        for (const auto& entry : data) {
            if (entry[0] >= xPos && entry[0] < xPos + 0.1) {
                sum += entry[1];
                count++;
            }
        }

        if (count > 0) {
            double average = sum / count;
            double errorSum = 0.0;
            for (const auto& entry : data) {
                if (entry[0] >= xPos && entry[0] < xPos + 0.1) {
                    errorSum += std::pow(entry[1] - average, 2);
                }
            }
            double sigma = std::sqrt(errorSum / (count - 1));
            
            // Print results to the output file
            outputFile << xPos << " " << average << " " << sigma << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
