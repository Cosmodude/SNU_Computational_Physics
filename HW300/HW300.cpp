#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a structure for the data
typedef struct {
    double *data;
    size_t size;
} DataSet;

// Function to read data from a file and determine the size
DataSet readData(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    DataSet dataSet;
    dataSet.data = NULL;
    dataSet.size = 0;

    double value;
    while (fscanf(file, "%lf", &value) == 1) {
        dataSet.size++;
        dataSet.data = (double *)realloc(dataSet.data, dataSet.size * sizeof(double));
        if (dataSet.data == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        dataSet.data[dataSet.size - 1] = value;
    }

    fclose(file);
    return dataSet;
}

// Function to calculate the average of a data set
double calculateAverage(const DataSet *dataSet) {
    double sum = 0.0;
    for (size_t i = 0; i < dataSet->size; i++) {
        sum += dataSet->data[i];
    }
    return sum / dataSet->size;
}

// Function to calculate the variance of the mean
double calculateVariance(const DataSet *dataSet, double average) {
    double sum = 0.0;
    for (size_t i = 0; i < dataSet->size; i++) {
        sum += pow(dataSet->data[i] - average, 2);
    }
    return sum / (dataSet->size - 1);
}

int main() {
    // Read data from files
    DataSet d1 = readData("data.104");
    DataSet d2 = readData("data.105");

    // Calculate results
    DataSet add, sub, mul, div;
    add.size = sub.size = mul.size = div.size = d1.size;
    add.data = (double *)malloc(add.size * sizeof(double));
    sub.data = (double *)malloc(sub.size * sizeof(double));
    mul.data = (double *)malloc(mul.size * sizeof(double));
    div.data = (double *)malloc(div.size * sizeof(double));

    for (size_t i = 0; i < d1.size; i++) {
        add.data[i] = d1.data[i] + d2.data[i];
        sub.data[i] = d1.data[i] - d2.data[i];
        mul.data[i] = d1.data[i] * d2.data[i];
        div.data[i] = d1.data[i] / d2.data[i];
    }

    // Calculate averages
    double avg_add = calculateAverage(&add);
    double avg_sub = calculateAverage(&sub);
    double avg_mul = calculateAverage(&mul);
    double avg_div = calculateAverage(&div);

    // Calculate variances
    double var_add = calculateVariance(&add, avg_add);
    double var_sub = calculateVariance(&sub, avg_sub);
    double var_mul = calculateVariance(&mul, avg_mul);
    double var_div = calculateVariance(&div, avg_div);

    // Print results to stat.data
    FILE *outputFile = fopen("stat.data", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file\n");
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "Add:\naverage = %.8lf\n", avg_add);
    fprintf(outputFile, "variance of the mean = %.8lf\n\n", var_add);

    fprintf(outputFile, "Sub:\naverage = %.8lf\n", avg_sub);
    fprintf(outputFile, "variance of the mean = %.8lf\n\n", var_sub);

    fprintf(outputFile, "Mul:\naverage = %.8lf\n", avg_mul);
    fprintf(outputFile, "variance of the mean = %.8lf\n\n", var_mul);

    fprintf(outputFile, "Div:\naverage = %.8lf\n", avg_div);
    fprintf(outputFile, "variance of the mean = %.8lf\n", var_div);

    fclose(outputFile);

    // Free allocated memory
    free(d1.data);
    free(d2.data);
    free(add.data);
    free(sub.data);
    free(mul.data);
    free(div.data);

    return 0;
}
