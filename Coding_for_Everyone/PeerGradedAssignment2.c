/* program that calculates the sine of a value between 0 and 1 (non inclusive)*/

#include <stdio.h>
#include <iostream>
#include <cmath>

int main(){
    double value;

    std::cout << "Enter a number between 0 and 1: ";
    std::cin >> value;

    if (value > 0 && value < 1){
        double result = std::sin(value);
        std::cout << "sine(" << value << ") = " << result << std::endl;

    }
    else {
        std::cout << "Error: must be between 0 and 1 (exclusive)." << std::endl;

    }


    return 0;

}