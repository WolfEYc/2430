#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "ArgumentManager.h"
using namespace std;
int vs = 0;

#define INT_MAX 99999

class doubleMatrix {
public:
	int vertexAmount;
	int** matrixPointer;
	ostream& outputFile;

	doubleMatrix(int vertexAmount, ostream& outputFile) : vertexAmount(vertexAmount), outputFile(outputFile)
	{
		matrixPointer = new int* [vertexAmount];
		for (int i = 0; i < vertexAmount; i++)
		{
			matrixPointer[i] = new int[vertexAmount];
		}

		for (int i = 0; i < vertexAmount; i++)
		{
			for (int j = 0; j < vertexAmount; j++)
			{
				if (i == j)
				{
					matrixPointer[i][j] = 0;
				}
				else
				{
					matrixPointer[i][j] = INT_MAX;
				}
			}

		}
	}

	bool oddVertexConnections(int rowNumber)
	{
		int numberOfVertex = 0;
		for (int i = 0; i < vertexAmount; i++)
		{
			if (matrixPointer[rowNumber][i] == 1)
				numberOfVertex++;
		}
		if (numberOfVertex % 2 == 0)
			return false;
		return true;
	}

	void printMatrix()
	{
		for (int i = 0; i < vertexAmount; i++)
		{
			for (int j = 0; j < vertexAmount; j++)
				outputFile << matrixPointer[i][j] << " | ";
			outputFile << endl;
		}
	}
};


struct edge {
	int first;
	int second;
	int weight;
};
bool allbool(vector<bool> b) {
	for (bool i : b)
		if (!i)return false;
	return true;
}
void format(vector<edge>& cons) {
	for (int i = 0; i < cons.size(); i++) {
		if (cons[i].second < cons[i].first) {
			int temp = cons[i].first;
			cons[i].first = cons[i].second;
			cons[i].second = temp;
		}
	}
	for (int i = 0; i < cons.size() - 1; i++) { //sorts by first connection
		for (int j = 0; j < cons.size() - i - 1; j++) {
			if (cons[j].first > cons[j + 1].first) {
				edge temp = cons[j];
				cons[j] = cons[j + 1];
				cons[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < cons.size() - 1; i++) { //sorts by second connection
		for (int j = 0; j < cons.size() - i - 1; j++) {
			if (cons[j].first == cons[j + 1].first && (cons[j].second > cons[j + 1].second)) {
				edge temp = cons[j];
				cons[j] = cons[j + 1];
				cons[j + 1] = temp;
			}
		}
	}
	cout << "Formatted connections" << endl;
	for (edge i : cons) {
		cout << i.first << " " << i.second << " " << i.weight << endl;
	}
	cout << endl;
}
vector<vector<edge>> highcons(vector<edge> cons) {
	vector<vector<edge>>v(vs);
	for (edge i : cons) {
		v[i.first].push_back(i);
		v[i.second].push_back(i);
	}
	return v;
}
bool allconnect(vector<edge> cons) {
	vector<bool> check(vs, false);
	if (cons.size() == 0 || cons[0].first != 0)return false;
	check[0] = true;
	for (edge i : cons) {
		if (check[i.first] == true || check[i.second] == true) {
			check[i.second] = true;
			check[i.first] = true;
		}
	}
	return allbool(check);
}
vector<vector<edge>> paths(vector<edge> cons) {
	//make function to find all possible paths
	vector<vector<edge>> v;
	return  v;
}
int concount(int node, vector<edge> cons) {
	int c = 0;
	for (edge i : cons)
		if (i.first == node || i.second == node)
			c++;
	return c;
}
int whichcon(int node, vector<edge> cons) {
	for (edge i : cons) {
		if (i.first == node)
			return i.second;
		if (i.second == node)
			return i.first;
	}
	return NULL;
}
bool checkedge(int first, int second, vector<edge> cons) {
	for (edge i : cons)
		if ((first == i.first || first == i.second) && (second == i.first || second == i.second))
			return true;
	return false;
}
bool oncewalk(vector<edge> cons) {
	vector<int> threenodes;
	int nodes = 0;
	int b = 0;
	for (int i = 0; i < vs; i++) {
		if (concount(i, cons) > 2)
			threenodes.push_back(i);
		if (concount(i, cons) == 1 && concount(whichcon(i, cons), cons) > 2)
			b++;
	}
	int c = 0;
	if (threenodes.size() > 2)
		for (int i = 0; i < threenodes.size(); i++)
			for (int j = 0; j < threenodes.size(); j++)
				if (i != j && checkedge(threenodes[i], threenodes[j], cons))
					c++;
	return c < 3 && b < 2;
}
int lowest(vector<int> v) {
	int low = v[0];
	for (int i : v)
		if (i < low)low = i;
	return low;
}
int wire(vector<edge> cons) {
	vector<int> lengths;




	return lowest(lengths);
}

int minimumIndexF(int keyIndex[], bool visitVertex[], int vertexAmount)
{
	int minimumValue = INT_MAX;
	int minimumIndex = 0;
	for (int i = 0; i < vertexAmount; i++)
	{
		if (keyIndex[i] < minimumValue && !visitVertex[i])
		{
			minimumValue = keyIndex[i];
			minimumIndex = i;
		}
	}
	return minimumIndex;
}

int shortestPathF(doubleMatrix myMatrix, int vertexAmount)
{
	int shortestPath = 0;

	int* parentIndex = new int[vertexAmount];
	int* keyIndex = new int[vertexAmount];
	bool* visitVertex = new bool[vertexAmount];

	for (int i = 0; i < vertexAmount; i++)
	{
		keyIndex[i] = INT_MAX;
		visitVertex[i] = false;
	}

	keyIndex[0] = 0;
	parentIndex[0] = -1;

	for (int i = 0; i < vertexAmount; i++)
	{
		int minimumIndex = minimumIndexF(keyIndex, visitVertex, vertexAmount);

		visitVertex[minimumIndex] = true;
		for (int j = 0; j < vertexAmount; j++)
		{
			if (myMatrix.matrixPointer[minimumIndex][j] && visitVertex[j] == false && myMatrix.matrixPointer[minimumIndex][j] < keyIndex[j])
			{
				parentIndex[j] = minimumIndex;
				keyIndex[j] = myMatrix.matrixPointer[minimumIndex][j];
			}
		}
	}
	for (int i = 0; i < vertexAmount; i++)
	{
		shortestPath = shortestPath + myMatrix.matrixPointer[i][parentIndex[i]];
	}

	return shortestPath;
}

int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream output(am.get("output"));
	input >> vs;
	vector<edge> connections;
	vector<bool> cools;
	int temp;
	int firstNumber;
	int secondNumber;
	int distance;
	doubleMatrix myMatrix(vs, output);
	while (input >> temp) {
		edge newedge;
		newedge.first = temp;
		firstNumber = temp;
		input >> temp;
		newedge.second = temp;
		secondNumber = temp;
		input >> temp;
		newedge.weight = temp;
		distance = temp;
		connections.push_back(newedge);

		myMatrix.matrixPointer[firstNumber][secondNumber] = distance;
		myMatrix.matrixPointer[secondNumber][firstNumber] = distance;
	}

	int shortestPath = shortestPathF(myMatrix, vs);
	vector<edge> cons = connections;
	format(connections);
	if (allconnect(connections)) {
		output << "1. Yes" << endl;
	}
	else {
		output << "1. No" << endl << "Bad";
		return 0;
	}

	bool singlePath;
	if (oncewalk(connections)) {
		output << "2. Yes" << endl;
		singlePath = true;
		cools.push_back(true);
	}
	else {
		singlePath = false;
		output << "2. No" << endl;
		cools.push_back(false);
	}

	output << "3. " << shortestPath << endl;
	vector<vector<edge>> vcons = highcons(cons);
	output << "4. ";
	bool juan = false;
	for (int i = 0; i < vcons.size(); i++) {
		if (vcons[i].size() >= 3) {
			if (juan == true) {
				output << ", ";
			}
			juan = true;
			output << i << "<-{";
			string ching = "";
			for (edge e : vcons[i]) {
				if (e.first != i)
					ching += to_string(e.first) + ",";
				else ching += to_string(e.second) + ",";
			}
			output << ching.substr(0, ching.size() - 1) << "}";
		}
	}
	output << endl;
	if (singlePath)
	{
		output << "Good" << endl;
	}
	else
	{
		output << "Fair" << endl;
	}
}