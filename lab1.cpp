#include <iostream>
#include "ArgumentManager.h"
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << std::endl;
	}
	ArgumentManager am(argc, argv);
	string in = am.get("input");
	string out = am.get("output");
	ofstream output(out);
	ifstream input(in);

	char first;
	char second;
	int op;
	int ans=0;
	bool broke = false;

	input >> op >> first >> second;
	
	if (op == 1) {
		ans = first + second;
	} else if (op == 2) {
		ans = first - second;
	}
	else {
		output << "ERROR: File not found";
		broke = true;
	}
	if (broke == false) {
		if (ans < 0) {
			output << "ERROR: negative result";
		}
		else {
			output << ans;
		}
	}
}

