/* you will use an array to calculate an average from raw data—specifically the average weight of 
the northern elephant seal (Mirounga angustirostris). You will submit a file with your program for your 
fellow learners to review, and you will review three of your fellow learners' programs. */

#include <stdio.h>

#define MAX_WEIGHTS 1000

int main() {
    FILE *file;
    double weights[MAX_WEIGHTS];
    int count = 0;
    double sum = 0.0, average = 0.0;

    // Open file for reading
    file = fopen("elephant_seal_data.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open elephant_seal_data.txt\n");
        return 1;
    }

    // Read weights into array
    while (fscanf(file, "%lf", &weights[count]) == 1 && count < MAX_WEIGHTS) {
        sum += weights[count];
        count++;
    }

    fclose(file); // close file

    if (count == 0) {
        printf("No data to calculate average.\n");
        return 1;
    }

    // Calculate and print average
    average = sum / count;
    printf("Average weight of northern elephant seals: %.2f\n", average);

    return 0;
}
