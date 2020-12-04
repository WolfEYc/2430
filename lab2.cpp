#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <fstream>
using namespace std;

struct node {
	string data;
	node* next = nullptr;
};

class link {
private:
	node* head = new node;
	int size=0;
public:
	int getSize() {
		return size;
	}
	void addnode(string datas) {
		node* current = head;
		node* add = new node;
		add->data = datas;
		while (current->next != nullptr) {			
			current = current->next;
		}
		current->next = add;
		size++;
	}
	string printback(string saved,int count) {
		node* current = head;
		string temp = saved;
		if (count == 0) {
			return saved;
		}
		for (int i = 0; i < count; i++) {
			current = current->next;
		}
		temp += current->data + " ";
		count--;
		return printback(temp,count);
	}
};

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << std::endl;
	}
	ArgumentManager am(argc, argv);
	string in = am.get("input");
	string out = am.get("output");	
	ifstream input(in);
	ofstream output(out);
	link local;
	string temp;	
	while (input >> temp) {	
		local.addnode(temp);
	}
	output << local.printback("",local.getSize());
	return 0;
}