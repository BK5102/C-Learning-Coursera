/*Write a C program that has a function that prints a table of values for sine and cosine between (0, 1). 
You will upload your program as a text file. */


#include <stdio.h>
#include <math.h>

void printSineCosineTable() {
    double x;
    printf(" x\t sin(x)\t\t cos(x)\n");
    printf("-------------------------------\n");

    for (x = 0.0; x <= 1.0; x += 0.1) {
        printf("%.1f\t %.6f\t %.6f\n", x, sin(x), cos(x));
    }
}

int main() {
    printSineCosineTable();
    return 0;
}
