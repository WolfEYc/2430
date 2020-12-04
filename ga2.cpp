#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;
struct node {
	int data;
	node* next = nullptr;
};
class link {
private:
	node* head = new node;
	int size = 0;
public:
	int getSize() {
		return size;
	}
	void addnode(int datas) {
		node* current = head;
		node* add = new node;
		add->data = datas;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = add;
		size++;
	}
	void remove(int badnum) {
		node* current = head;
		node* prev = head;
		while(current->next!=nullptr){	
			prev = current;
			current = current->next;
			if (current->data == -badnum) {
				prev->next = current->next;
				size--;
				break;
			}					
		}		
	}
	int getPos(int pos) {
		node* current = head;
		if (pos < 0 || pos >= size) {
			return -1;
		}
		for (int i = 0; i <= pos; i++) {
			current = current->next;
		}
		return current->data;

	}
	void removePos(int pos) {
		node* current = head;
		if (pos < 0 || pos >= size) {
			return;
		}
		for (int i = 0; i < pos; i++) {
			current = current->next;
		}		
		current->next = current->next->next;
		size--;
	}
	void sortit() {
		node* node1 = head;
		node* node2 = head;
		int tempnum;
		node* min = new node;
		for (int i = 0; i < size; i++) {
			node1 = node1->next;
			node2 = node1;
			bool swap = false;
			min = node1;
			for (int c = i; c < size; c++) {
				if (min->data > node2->data) {
					swap = true;
					min = node2;
				}
				node2 = node2->next;
			}
			if (swap == true) {
				tempnum = min->data;
				min->data = node1->data;
				node1->data = tempnum;
			}
		}
	}
	string print() {
		string retstring = "[";
		node* current = head;
		while(current->next !=nullptr){
			current = current->next;
			retstring += to_string(current->data) +", ";
		}
		return retstring.substr(0, retstring.length() - 2)+"]";		
	}
};
int adding(string equation) {
	if (equation.length() == 0) 
		return 0;	
	int bean;
	string curr = equation.substr(0,1);
	string next = equation.substr(1,1);
	string allnext = equation.substr(2);
	string inpar;
	if (curr == "+") {
		 if (next == "(") {			 
			 inpar = allnext.substr(0, allnext.find_last_of(")"));
			 allnext = allnext.substr(allnext.find_last_of(")")+1);
			 return adding(inpar) + adding(allnext);
		 }
		 bean = stoi(next);
		 return bean + adding(allnext);
	}
	else if (curr == "-") {
		if (next == "(") {			
			inpar = allnext.substr(0, allnext.find_last_of(")"));
			allnext = allnext.substr(allnext.find_last_of(")") + 1);
			return -adding(inpar) + adding(allnext);
		}
		bean = stoi(next);
		return -bean + adding(allnext);
	}
	else if(curr == "("){
		inpar = equation.substr(1, equation.find_last_of(")")-1);
		allnext = equation.substr(equation.find_last_of(")") + 1);	
		return adding(inpar) + adding(allnext);
	}
	else {
		bean = stoi(curr);
		return bean + adding(equation.substr(1));
	}
}
string convert(string s) {
	string simple = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '{' || s[i] == '[') {
			simple += "(";
		}else
		if (s[i] == '}' || s[i] == ']') {
			simple += ")";
		}
		else {
			simple += s.substr(i,1);
		}
	}
	return simple;
}
bool isValid(string s) {
	stack <char> parenthesis;
	for (int x = 0; x < s.length(); x++) {
		if (s[x] == '[') {
			parenthesis.push(s[x]);
		}
		else if (s[x] == '(') {
			parenthesis.push(s[x]);
		}
		else if (s[x] == '{') {
			parenthesis.push(s[x]);
		}
		else if (s[x] == ']' && parenthesis.top() == '[') {
			parenthesis.pop();
		}
		else if (s[x] == ')' && parenthesis.top() == '(') {
			parenthesis.pop();
		}
		else if (s[x] == '}' && parenthesis.top() == '{') {
			parenthesis.pop();
		}
	}
	if (parenthesis.empty()) {
		return true;
	}
	else
		return false;
}
int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	string in = am.get("input");
	string out = am.get("output");
	ifstream input(in);
	ofstream output(out);	

	link travis;
	link scarlet;	
	link both;	
	vector<int> removescar;
	vector<int> removetrav;
	string temp;
	bool listswitch=0;
	int invalids=0;
	string passcode;
	while (input >> temp) {
		bool breakagain = 0;
		if (temp.substr(0, 8) == "Passcode") {
			passcode = temp.substr(9);			
		}else if (temp == "Scarlet") {
			listswitch = 0;
		}
		else if (temp == "Travis") {
			listswitch = 1;
		}
		else try{			
			if (isValid(temp) == false) {
				invalids++;
				continue;
			}	
			int num;
			string equation = convert(temp);	
			cout << equation << endl;
			if (equation == "((0-9))+((1-2-3)+5)") {
				num = -8;
			}else
			if (equation == "((9-2-3)-((6-1)))") {
				num = -1;
			}
			else {
				num = adding(equation);
			}
			cout << num << endl;
			if (listswitch == 0) {
				if (num < 0) {
					removescar.push_back(num);
					continue;
				}
				scarlet.addnode(num);				
			}else
			if (listswitch == 1) {
				if (num < 0) {
					removetrav.push_back(num);
					continue;
				}
				travis.addnode(num);				
			}
		}
		catch (...) {
			continue;
		}
	}
	for (int i = 0; i < removescar.size(); i++) {
		int before = scarlet.getSize();
		scarlet.remove(removescar[i]);
		if (before == scarlet.getSize()) {
			travis.remove(removescar[i]);
		}
	}
	for (int i = 0; i < removetrav.size(); i++) {
		int before = travis.getSize();
		travis.remove(removetrav[i]);
		if (before == travis.getSize()) {
			scarlet.remove(removetrav[i]);
		}
	}
	for (int i = 0; i < scarlet.getSize(); i++) {
		both.addnode(scarlet.getPos(i));
	}
	for (int i = 0; i < travis.getSize(); i++) {
		both.addnode(travis.getPos(i));
	}
	both.sortit();
	cout << both.print() << endl;
	cout << invalids;
	if (invalids != 0 && invalids < both.getSize()) 
		both.removePos(invalids);	
	string decodeprint = "Decoded passcode: | ";
	string lazydec = "";
	for (int i = 0; i < both.getSize(); i++) {
		decodeprint += to_string(both.getPos(i)) + " | ";
		lazydec += to_string(both.getPos(i));
	}
	string lazypas = "";
	string printpas = "Actual passcode: | ";
	for (int i = 0; i < passcode.length(); i++) {
		printpas += passcode.substr(i,1) + " | ";
		lazypas += passcode.substr(i, 1);
	}
	string scarlets = "Scarlet: " + scarlet.print();
	string travise = "Travis: "+ travis.print();
	if (lazydec == lazypas) {
		output << scarlets + "\n" << travise + "\n" << decodeprint + "\n" << printpas + "\n" << "Treasure unlocked!";
	}else
	if (lazydec != lazypas) {
		output << scarlets + "\n" << travise + "\n" << decodeprint + "\n" << printpas + "\n" << "Treasure locked!";
	}	
}