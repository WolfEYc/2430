#include <iostream>
#include <string>
#include "ArgumentManager.h"
#include <fstream>
using namespace std;

struct node {//node struct
	string data;
	double time;
	node* next = nullptr;
};

class queue {
private:
	node* head = new node;
	int size = 0; //keeps track of size
public:
	void push(string data,double time) {//adds node to end
		node* newnode = new node;
		node* curr = head;
		newnode->data = data;
		newnode->time = time;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = newnode;
		size++;
	}	
	void sort(){//sorts it
		for (int i = 0; i < size-1; i++) {
			node* juan = head->next;
			node* jose = juan->next;
			for (int j = 0; j < size - i - 1; j++) {
				if (jose->time < juan->time) {
					double josetim = jose->time;
					string josestr = jose->data;
					jose->time = juan->time;
					jose->data = juan->data;
					juan->time = josetim;
					juan->data = josestr;
				}
				juan = juan->next;
				jose = jose->next;
			}
		}
	}
	void output(ofstream& output) {//outputs it
		node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
			output << curr->data<<endl;
		}
	}
};

double findnum(string str){//gets the double in the str
	string tempnum = "";
	for (int i = str.length() - 1; i >= 0; i--) {
		if (str[i] == ' ')break;
		tempnum = str.substr(i, 1) + tempnum;
	}
	return stod(tempnum);
}

string bonknum(string str) {//gets the string without the number at the end
	string tempstr = "";
	string fullstr = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			fullstr += tempstr;
			tempstr = "";
		}
		tempstr += str.substr(i, 1);
	}
	return fullstr;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << endl;
	}
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream output(am.get("output"));

	string temp;
	queue mememan;	

	while (getline(input, temp)) {
		if (temp.length() != 0) {
			mememan.push(bonknum(temp), findnum(temp));//inputs it
		}
	}

	mememan.sort();//sorts it

	mememan.output(output); //outputs it
}