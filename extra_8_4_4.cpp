#include <iostream>
using namespace std;
int main() {
    int m = 5;    // m is an int storing 5
    int* ptr;     // a pointer to an int
    ptr = &m;     // assign to ptr the
                  // address of m
    cout << ptr << endl;
    return 0;
}
