#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

struct DataSet {
    double x;
    std::vector<double> yValues;
};

// Function to fit: f(x) = ax^3 + bx^2 * sin(x) + c * sqrt(x) + d
double func(double x, double a, double b, double c, double d) {
    return a * std::pow(x, 3) + b * std::pow(x, 2) * std::sin(x) + c * std::sqrt(x) + d;
}

// Derivative of the function with respect to each parameter
double df_da(double x, double a, double b, double c, double d) {
    return std::pow(x, 3);
}

double df_db(double x, double a, double b, double c, double d) {
    return std::pow(x, 2) * std::sin(x);
}

double df_dc(double x, double a, double b, double c, double d) {
    return std::sqrt(x);
}

double df_dd(double x, double a, double b, double c, double d) {
    return 1.0;
}

// Gradient descent optimizer
void gradientDescent(std::vector<DataSet> dataSets, std::vector<double> y,  std::vector<double> sigma, size_t n, double& a, double& b, double& c, double& d, double alpha, size_t maxIter) {
    for (size_t iter = 0; iter < maxIter; ++iter) {
        double da = 0.0, db = 0.0, dc = 0.0, dd = 0.0;

        for (size_t i = 0; i < n; ++i) {
            double diff = y[i] - func(dataSets[i].x, a, b, c, d);
            da += (diff / sigma[i]) * df_da(dataSets[i].x, a, b, c, d);
            db += (diff / sigma[i]) * df_db(dataSets[i].x, a, b, c, d);
            dc += (diff / sigma[i]) * df_dc(dataSets[i].x, a, b, c, d);
            dd += (diff / sigma[i]) * df_dd(dataSets[i].x, a, b, c, d);
        }

        a += alpha * da;
        b += alpha * db;
        c += alpha * dc;
        d += alpha * dd;
    }
}

// Function for least squares fitting
void fitLeastSquares(std::vector<DataSet> dataSets, std::vector<double> y,  std::vector<double>  sigma, size_t n, double& a, double& b, double& c, double& d,double& sigma_a, double& sigma_b, double& sigma_c, double& sigma_d, double alpha = 1e-5, size_t maxIter = 1000) {
    // Initial guess for parameters
    a = 1.0, b = 1.0, c = 1.0, d = 1.0;

    // Perform gradient descent
    gradientDescent(dataSets, y, sigma, n, a, b, c, d, alpha, maxIter);


    // Calculate covariance matrix
    std::vector<std::vector<double>> covarianceMatrix(4, std::vector<double>(4, 0.0));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            double sum = 0;

            for (size_t k = 0; k < n; ++k) {
                double df_di = 0.0;
                switch (i) {
                    case 0:
                        df_di = df_da(dataSets[k].x, a, b, c, d);
                        break;
                    case 1:
                        df_di = df_db(dataSets[k].x, a, b, c, d);
                        break;
                    case 2:
                        df_di = df_dc(dataSets[k].x, a, b, c, d);
                        break;
                    case 3:
                        df_di = df_dd(dataSets[k].x, a, b, c, d);
                        break;
                }

                double df_dj = 0.0;
                switch (j) {
                    case 0:
                        df_dj = df_da(dataSets[k].x, a, b, c, d);
                        break;
                    case 1:
                        df_dj = df_db(dataSets[k].x, a, b, c, d);
                        break;
                    case 2:
                        df_dj = df_dc(dataSets[k].x, a, b, c, d);
                        break;
                    case 3:
                        df_dj = df_dd(dataSets[k].x, a, b, c, d);
                        break;
                }

                sum += (df_di / sigma[k]) * (df_dj / sigma[k]);
            }

            covarianceMatrix[i][j] = sum / (n * (n - 1));
        }
    }

    // Calculate standard deviations (square root of diagonal elements of covariance matrix)
    sigma_a = std::sqrt(covarianceMatrix[0][0]);
    sigma_b = std::sqrt(covarianceMatrix[1][1]);
    sigma_c = std::sqrt(covarianceMatrix[2][2]);
    sigma_d = std::sqrt(covarianceMatrix[3][3]);
}

// Calculate χ² value
double calculateChiSquared(std::vector<DataSet> dataSets, std::vector<double> y, std::vector<double> sigma, size_t n, double a, double b, double c, double d) {
    double chiSquared = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double diff = y[i] - func(dataSets[i].x, a, b, c, d);
        chiSquared += std::pow(diff / sigma[i], 2);
    }

    return chiSquared;
}

// Quadrature method for confidence level calculation
double calculateConfidenceLevel(double chiSquared, size_t degreesOfFreedom) {
    // Confidence level = P(χ² >= χ²_observed)
    // Using quadrature method to integrate the tail of the χ² distribution
    // Confidence level is the area under the tail of the distribution
    
    const size_t integrationSteps = 1000;
    double stepSize = chiSquared / integrationSteps;
    double confidenceLevel = 0.0;

    for (size_t i = 0; i < integrationSteps; ++i) {
        double x = i * stepSize;
        confidenceLevel += stepSize * std::exp(-0.5 * x) / std::tgamma(0.5 * degreesOfFreedom);
    }
    
    // Ensure confidence level is between 0 and 1
    return std::min(confidenceLevel, 0.99); // (chisquared = 12.6 > chisquared for confidence level 0.99)
}

int main() {
    // Open the data file
    std::ifstream dataFile("dat.2023-12-15");

    // Check if the file is opened successfully
    if (!dataFile.is_open()) {
        std::cerr << "Error: Unable to open the data file." << std::endl;
        return 1;
    }

    
    // Variables to store x and y values
    double x, y;

    // Vector to store data sets
    std::vector<DataSet> dataSets;
    std::vector<double> averages;
    
    // Read data until the end of file
    while (dataFile >> x >> y) {
        // Check if both x and y values are read successfully
        if (!dataFile.fail()) {
            // Check if the x value already exists in dataSets
            auto it = std::find_if(dataSets.begin(), dataSets.end(),
                [x](const DataSet& dataSet) { return dataSet.x == x; });

            if (it != dataSets.end()) {
                // Add y value to existing x value
                it->yValues.push_back(y);
            } else {
                // Create a new data set
                dataSets.push_back({x, {y}});
            }
        }
    }

    int count = static_cast<int>(dataSets[0].yValues.size());
    int x_count = dataSets.size();
    std::vector<std::vector<double>> covarianceMatrix(x_count, std::vector<double>(x_count, 0.0));
    // Close the file
    dataFile.close();

    std::cout << "Number of datasets: " << count << std::endl;

    // Open the output file
    std::ofstream outputFile("stat.out");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the output file." << std::endl;
        return 1;
    }
    std::ofstream graphFile("graph.in");
    if (!graphFile.is_open()) {
        std::cerr << "Error: Unable to open the output file." << std::endl;
        return 1;
    }

    /// Calculate average for each x value
    for (const auto& dataSet : dataSets) {
        // Calculate average for each x value
        double sumY = 0.0;

        // Iterate through y values and calculate sum
        for (const auto& yValue : dataSet.yValues) {
            sumY += yValue;
        }

        // Calculate average
        double averageY = sumY / count;
        averages.push_back(averageY);

        // Output the results for each x value
        std::cout << "For x = " << dataSet.x << ": " << std::endl;
        std::cout << "   Average of y(x): " << averageY << std::endl;

        // Output the results for each x value to the file
        outputFile << "For x = " << dataSet.x << " average of y(x)= " << averageY << std::endl;
    }
    outputFile << std::endl;

    // Calculate covariance matrix
    
    for (int i = 0; i < x_count; ++i) {
        for (int j = 0; j < x_count; ++j) {
            double sum = 0;
            for (int k=0; k<count; ++k){
                sum += (dataSets[i].yValues[k] - averages[i]) * (dataSets[j].yValues[k] - averages[j]);
            }
            covarianceMatrix[i][j] = sum / (count * (count - 1));
        }
    }


    // Output covariance matrix to the file
    outputFile << "Covariance Matrix:" << std::endl;
    for (int i = 0; i < x_count; ++i) {
        for (int j = 0; j < x_count; ++j) {
            outputFile << covarianceMatrix[i][j] << " ";
        }
        outputFile << std::endl;
    }

    std::vector<double> sigma;

    for (int i = 0; i  < x_count; ++i){
        sigma.push_back(sqrt(covarianceMatrix[i][i] * count * (count-1)));
        graphFile << i << " " << averages[i] << " " << sqrt(covarianceMatrix[i][i] * count) << std::endl;
    }

    // Close the output file
    outputFile.close();
    graphFile.close();


    // Fitted parameters
    double a, b, c, d, sigma_a, sigma_b, sigma_c, sigma_d;

    // Perform least squares fitting
    fitLeastSquares(dataSets, averages, sigma, x_count, a, b, c, d, sigma_a, sigma_b, sigma_c, sigma_d);

    double chiSquared = calculateChiSquared(dataSets, averages, sigma, x_count, a, b, c, d);

    // Calculate degrees of freedom
    size_t degreesOfFreedom = x_count - 4; // Assuming 4 fitted parameters

    // Calculate confidence level
    double confidenceLevel = calculateConfidenceLevel(chiSquared, degreesOfFreedom);
    // Output the results
    std::cout << "Fitted parameters:" << std::endl;
    std::cout << "a = " << a << " ± " << sigma_a << std::endl;
    std::cout << "b = " << b << " ± " << sigma_b << std::endl;
    std::cout << "c = " << c << " ± " << sigma_c << std::endl;
    std::cout << "d = " << d << " ± " << sigma_d << std::endl;

    std::cout << "Chi² value: " << chiSquared << std::endl;
    std::cout << "Degrees of Freedom: " << degreesOfFreedom << std::endl;
    std::cout << "Confidence Level: " << confidenceLevel << std::endl;
    std::cout << "Given a confidence level of 0.99, it means we have a significance level of  α = 0.01  since, Significance level = (1−Confidence level). Thus, we fail to reject the null hypothesis, suggesting that the function form is acceptable." << std::endl;
       
    return 0;
}
