#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    // Open the data file for reading
    FILE *file = fopen("data.104", "r");
    if (file == NULL) {
        printf("Error opening the data file.\n");
        return 1;
    }

    // Variables for data processing
    double sum = 0.0;
    double sumSquared = 0.0;
    int count = 0;

    // Read data and calculate sum and sum of squares
    double value;
    while (fscanf(file, "%lf", &value) == 1) {
        sum += value;
        sumSquared += value * value;
        count++;
    }

    // Close the file
    fclose(file);

    if (count == 0) {
        printf("No data found in the file.\n");
        return 1;
    }

    // Calculate average, variance, and variance of the mean
    double average = sum / count;
    double variance = (sumSquared / count) - (average * average);
    double varianceOfMean = variance / (count - 1);

    // Open a file for writing statistics
    FILE *statFile = fopen("stat.data", "w");
    if (statFile == NULL) {
        printf("Error opening the statistics file.\n");
        return 1;
    }

    // Print statistics to the file
    fprintf(statFile, "average = %lf\n", average);
    fprintf(statFile, "variance = %lf\n", variance);
    fprintf(statFile, "variance of the mean = %lf\n", varianceOfMean);

    // Close the statistics file
    fclose(statFile);

    return 0;
}
