/* Open and read a file of integers into an array that is created with the first integer telling you 
how many to read.
So  4  9  11  12  15  would mean create an int array size 4 and read in the remaining 4 values into data[].
Then compute their average as a double and their max  as an int.  Print all this out neatly to the screen and 
to an output file named answer-hw3.*/


#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *input, *output;
    int count, max;
    double sum = 0;

    input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    // Read the count of numbers
    if (fscanf(input, "%d", &count) != 1 || count <= 0) {
        printf("Error: Invalid count value in input file.\n");
        fclose(input);
        return 1;
    }

    // Dynamically allocate memory for data
    int *data = (int *) malloc(count * sizeof(int));
    if (data == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(input);
        return 1;
    }

    // Read the integers into the array
    for (int i = 0; i < count; i++) {
        if (fscanf(input, "%d", &data[i]) != 1) {
            printf("Error: Not enough integers in the input file.\n");
            free(data);
            fclose(input);
            return 1;
        }
        sum += data[i];
        if (i == 0 || data[i] > max)
            max = data[i];
    }

    fclose(input);

    double average = sum / count;

    // Open output file
    output = fopen("answer-hw3.txt", "w");
    if (output == NULL) {
        printf("Error: Could not open output file.\n");
        free(data);
        return 1;
    }

    // Print to screen and output file
    printf("Read %d integers:\n", count);
    fprintf(output, "Read %d integers:\n", count);

    for (int i = 0; i < count; i++) {
        printf("%d ", data[i]);
        fprintf(output, "%d ", data[i]);
    }
    printf("\nAverage: %.2f\n", average);
    printf("Maximum: %d\n", max);

    fprintf(output, "\nAverage: %.2f\n", average);
    fprintf(output, "Maximum: %d\n", max);

    fclose(output);
    free(data);

    return 0;
}
