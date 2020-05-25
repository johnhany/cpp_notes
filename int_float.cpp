#include <iostream>

using namespace std;


int main() {
    // Number of `1`s in binary format of `int`
    int x = 7;
    int count = 0;
    while (x) {
        x = x & (x-1);
        count++;
    }
    cout << count << endl;


    // Check if `x == 2^k`
    x = 16;
    bool flag = !(x & (x-1));
    cout << flag << endl;
    x = 15;
    flag = !(x & (x-1));
    cout << flag << endl;


    // Average of `int` `x` and `y`
    x = 5;
    int y = 8;
    int avg = (x & y) + ((x ^ y) >> 1);
    cout << avg << endl;


    int int_max = (int)((~((unsigned int) 0)) >> 1);
    int int_min = ~int_max;
    cout << int_min << ", " << int_max << endl;

    return 0;
}