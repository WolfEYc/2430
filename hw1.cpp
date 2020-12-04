#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include <iomanip>
#include <vector>
using namespace std;

//to decode the matrix!!
string decode(int maxR, int maxC, int curR, int curC, int d, string str, vector<vector<string>> mat) {
	//0=c+1 1=r+1 2=c-1 3=r-1

	int c = curC;
	int r = curR;
	int dir = d;
	bool goback = false;
	bool stopper = false;

	string stradd = str;

	vector<vector<string>> nmat(maxR, vector<string>(maxC));

	int x, y;
	for (x = 0; x < maxR; x++) {
		for (y = 0; y < maxC; y++) {
			nmat[x][y] = mat[x][y];
		}
	}
	nmat[0][0] = "aa";

	//will get the next thing in the direction and add it to stradd
	//will go to next direction and check if current direction gets vibed
	do {

		if (dir == 0 && curC + 1 < maxC && nmat[curR][curC + 1] != "aa") {
			stradd = stradd + mat[curR][curC + 1];
			nmat[curR][curC + 1] = "aa";
			break;
		}
		else {
			if (dir == 0)dir++;
			
		}
		if (dir == 1 && curR + 1 < maxR && nmat[curR + 1][curC] != "aa") {
			stradd = stradd + mat[curR + 1][curC];
			nmat[curR + 1][curC] = "aa";
			break;
		}
		else {
			if (dir == 1)dir++;
			
		}
		if (dir == 2 && curC - 1 >= 0 && nmat[curR][curC - 1] != "aa") {
			stradd = stradd + mat[curR][curC - 1];
			nmat[curR][curC - 1] = "aa";
			break;
		}
		else {
			if (dir == 2)dir++;
		}
		if (dir == 3 && curR - 1 >= 0 && nmat[curR - 1][curC] != "aa") {
			stradd = stradd + mat[curR - 1][curC];
			nmat[curR - 1][curC] = "aa";
			break;
		}
		else {
			if (dir == 3)dir = 0;
			if (stopper == false) {
				goback = true;
				stopper = true;
			}
			else {
				break;
			

			}
		}
	} while (goback == true);

	//returns stradd as the string if no changes get made in the loops above
	if (stradd == str) {
		return stradd;
	}
	else {
		//sets the next location according to direction
		if (dir == 0)c += 1;
		if (dir == 1)r += 1;
		if (dir == 2)c -= 1;
		if (dir == 3)r -= 1;
		//recurs the code with the new string
		return decode(maxR, maxC, r, c, dir, stradd, nmat);
	}
	return "nah";
}

string outcur(int left, vector<string> strs) {
	if (left == 0) {
		return "";
	}
	return strs[left - 1]+ "\n" + outcur(left - 1, strs);
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << std::endl;
	}
	ArgumentManager am(argc, argv);
	string in = am.get("input");
	string out = am.get("output");
	ofstream writefile(out);
	ifstream readfile(in);

	//comment this out after
	writefile.close();

	vector<string> strings;

	string dim, line, find;

	find = "start";
	readfile >> line;

	//goes to start
	while (line != find) {
		readfile >> line;
	}

	strings.push_back("start");

	while (69 == 69) {
		//stores the strings for dimentions
		readfile >> dim;
		

		//stores row and col
		const int row = stoi(dim.substr(0, 1));
		const int col = stoi(dim.substr(2, 1));

		vector<vector<string>> matrix(row, vector<string>(col));

		int x, y;
		for (x = 0; x < row; x++) {
			for (y = 0; y < col; y++) {
				
				readfile >> matrix[x][y];
			}
		}

		string outputstr = decode(row, col, 0, 0, 0, matrix[0][0], matrix);
		if (outputstr == "finish")break;

		strings.push_back(outputstr);

		//gives last thing in the strings array
		find = strings.back();

		while (line != find) {
			if (readfile.eof() == true) {
				readfile.clear();
				readfile.seekg(0);
			}
			readfile >> line;
		}
	}

	//comment this out too
	writefile.open("output.txt");
	cout << outcur(strings.size(), strings);
	writefile << outcur(strings.size(), strings);

	return 0;
}