#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
	
	ArgumentManager am(argc, argv);
	string in = am.get("input");
	string out = am.get("output");

	
	
	//change this filename to the filename of the input file, this code will write to the output.txt file.
	ifstream readfile(in);
	ofstream writefile(out);
	writefile.close();
	string f;
	readfile >> f;
	const int size = stoi(f);


	

	int** matrix = new int*[size];
	double sizetwo = size * size;
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}

	int x, y;
	string temp;
	for (x = 0; x < size; x++) {
		for (y = 0; y < size; y++) {
			readfile >> temp;
			matrix[x][y]=stoi(temp);
		}
	}
	string op;
	string oper;
	readfile >> oper;
	int num=0;
	if (oper.length() > 1) {
		op = oper.substr(0, 1);
		num = stoi(oper.substr(1, 1));
	}
	else {
		op = oper.substr(0, 1);
	}

	double counter = 0.0;
	if (op == "e" ) {
		for (x = 0; x < size; x++) {
			for (y = 0; y < size; y++) {
				if (matrix[x][y] % 2 == 0) {
					counter+=1.0;
				}
			}
		}
	}

	if (op == "o") {
		for (x = 0; x < size; x++) {
			for (y = 0; y < size; y++) {
				if (matrix[x][y] % 2 == 1) {
					counter+=1.0;
				}
			}
		}
	}

	if (op == "=") {
		
		


		for (x = 0; x < size; x++) {
			for (y = 0; y < size; y++) {
				if (matrix[x][y] == num) {
					counter+=1.0;
				}
			}
		}
	}

	if (op == "<") {

		


		for (x = 0; x < size; x++) {
			for (y = 0; y < size; y++) {
				if (matrix[x][y] < num) {
					counter+1.0;
				}
			}
		}
	}
	if (op == ">") {

		


		for (x = 0; x < size; x++) {
			for (y = 0; y < size; y++) {
				if (matrix[x][y] > num) {
					counter+=1.0;
				}
			}
		}
	}
	
	cout << counter <<endl;
	cout << sizetwo <<endl;
	double ans = counter / sizetwo;
	cout << ans <<endl;
	

	writefile.open(out);
	cout << fixed << setprecision(2) << ans;
	 writefile << fixed << setprecision(2) << ans;
	
	return 0;
}