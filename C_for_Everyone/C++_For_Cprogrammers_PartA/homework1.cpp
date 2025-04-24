/*   Convert this program to C++

*   change to C++ io

*   change to one line comments

*   change defines of constants to const

*   change array to vector<>

*   inline any short function

*/

#include <iostream>       // replaces stdio.h
#include <vector>         // replaces C arrays

const int N = 40;         // replaces #define N 40

// inlined sum logic inside main, removing need for function
int main() {
    int accum = 0;                   // variable to store the sum
    std::vector<int> data(N);       // vector replacing int data[N]

    for (int i = 0; i < N; ++i)
        data[i] = i;                // populate vector with values 0..N-1

    for (int i = 0; i < N; ++i)
        accum += data[i];          // sum elements of the vector

    std::cout << "sum is " << accum << std::endl; // C++ style output
    return 0;
}
