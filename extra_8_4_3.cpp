#include<iostream>
using namespace std;

template <typename Type>
Type sqr(Type x) {
	return x * x;
}

int main() {
	cout << "3 squared is " << sqr<int>(3) << endl;
	cout << "Pi squared is " << sqr<double>(3.141592653589793) << endl;

	return 0;
}
