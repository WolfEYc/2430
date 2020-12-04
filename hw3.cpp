#include "ArgumentManager.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//nodes
struct node {	
	string data;
	node* next = nullptr;
};
//checks if its an operator
bool isOperator(char x)
{
	switch (x) {
	case '+':
	case '-':
	case '/':
	case '*':
		return true;
	}
	return false;
}
string preToPost(string pre_exp);
string postToPre(string som);

//link class
class link {
private:
	node* head = new node;
	int size = 0;
public:
	int getSize() {
		return size;
	}
	void push(string datas) {
		node* current = head;
		node* add = new node;
		add->data = datas;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = add;
		size++;
	}		
	string pushReserve(string type) {
		int counter = 0;
		node* current = head;
		node* prev = head;
		string currpref;
		while (current->next != nullptr) {
			if (counter > size) {
				break;
			}
			prev = current;
			current = current->next;
			currpref = current->data.substr(0, current->data.find(":"));
			if (type == "prefix") {
				if (currpref == "prefix") {
					prev->next = prev->next->next;
					size--;
					return current->data;
				}
			}
			else
			if (type == "postfix") {
				if (currpref == "postfix") {
					prev->next = prev->next->next;
					size--;
					return current->data;
				}
			}
			else
			if (type == "all") {
				prev->next = prev->next->next;
				size--;
				return current->data;						
			}
			else {//by pos
				if (stoi(type) < 0 || counter == stoi(type)) {
					prev->next = prev->next->next;
					size--;
					return current->data;
				}
			}
			counter++;
		}
		return"";
	}
	void convertList(string type) {
		int counter = 0;
		node* current = head;
		string currpref;
		string currdata;
		while (current->next != nullptr) {
			if (counter > size) {
				break;
			}
			current = current->next;
			currpref = current->data.substr(0,current->data.find(":"));
			currdata = current->data.substr(current->data.find(":")+1);
			if (type == "prefix") {
				if (currpref == "prefix") {
					current->data = "postfix:" + preToPost(currdata);
				}				
			}
			else
			if (type == "postfix") {
				if (currpref == "postfix") {
					current->data = "prefix:" + postToPre(currdata);
				}
			}
			else
			if (type == "all") {
				if (currpref == "prefix") {
					current->data = "postfix:" + preToPost(currdata);
				}
				else {
					current->data = "prefix:" + postToPre(currdata);
				}
			}
			else {//by pos
				if (stoi(type) < 0 || counter == stoi(type)) {
					if (currpref == "prefix") {
						current->data = "postfix:" + preToPost(currdata);
					}
					else {
						current->data = "prefix:" + postToPre(currdata);
					}
					break;
				}				
			}
			counter++;
		}
	}
	string printList() {
		string retstring="List:";
		node* current = head;
		while (current->next != nullptr) {
			current = current->next;
			retstring += "\n"+current->data;
		}
		if (retstring == "List:") return retstring + "\n" + "EMPTY";
		
		return retstring;
	}
	string printListBackwards(int counter) {		
		if (size == 0) {
			return "EMPTY";
		}
		if (counter == -1) {
			return"";
		}	
		node* current = head;		
		for(int i=0;i<=counter;i++){
			current = current->next;			
		}
		counter--;
		return current->data+"\n" + printListBackwards(counter);	
	}
	void popReserve(string pop, int pos) {		
		if (pos < 0) {
			pos = 0;
		}else
		if (pos > size) {
			pos = size;
		}
		node* current = head;
		node* prev = head;
		node* addnode = new node;
		addnode->data = pop;
		for (int i = 0; i <= pos; i++) {
			prev = current;
			current = current->next;			
		}
		size++;
		addnode->next = current;
		prev->next = addnode;
	}
	string get(int pos) {
		if (pos < 0 || pos >= size) {
			return "EMPTY";
		}
		node* curr = head;
		for (int i = 0; i <= pos; i++) {
			curr = curr->next;
		}
		return curr->data;
	}	
	string top() {
		return get(size - 1);
	}
	void set(int pos,string data) {
		if (pos < 0 || pos >= size) {
			return;
		}
		node* curr = head;
		for (int i = 0; i <= pos; i++) {
			curr = curr->next;
		}
		curr->data = data;
	}
	void convertReserve() {
		string tempe = top();
		string currpref = tempe.substr(0, tempe.find(":"));
		string currdata = tempe.substr(tempe.find(":") + 1);

		if (currpref == "prefix") {
			tempe = "postfix:" + preToPost(currdata);
		}
		else {
			tempe = "prefix:" + postToPre(currdata);
		}
		set(size - 1, tempe);
	}
	void pop() {
		node* curr = head;
		node* prev = head;
		while (curr->next != nullptr) {
			prev = curr;
			curr = curr->next;
		}
		size--;
		prev->next = nullptr;
	}
};

//fix conversion
string preToPost(string pre_exp) {

	link s;

	// length of expression 
	int length = pre_exp.size();

	// reading from right to left 
	for (int i = length - 1; i >= 0; i--) {

		// check if symbol is operator 
		if (isOperator(pre_exp[i])) {

			// pop two operands from stack 
			string op1 = s.top(); s.pop();
			string op2 = s.top(); s.pop();

			// concat the operands and operator 
			string temp = op1 + op2 + pre_exp[i];

			// Push string temp back to stack 
			s.push(temp);
		}

		// if symbol is an operand 
		else {

			// push the operand to the stack 
			s.push(string(1, pre_exp[i]));
		}
	}

	// stack contains only the Postfix expression 
	return s.top();
}
string postToPre(string post_exp)
{
	link s;

	// length of the expression 
	int length = post_exp.size();

	// reading from left to right
	for (int i = 0; i < length; i++) {

		// check if symbol is operator 
		if (isOperator(post_exp[i])) {

			// pop two operands from stack 
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();

			// concat the operands and operator 
			string temp = post_exp[i] + op2 + op1;

			// Push string temp back to stack 
			s.push(temp);
		}

		// if symbol is an operand 
		else {

			// push the operand to the stack 
			s.push(string(1, post_exp[i]));
		}
	}

	// stack[0] contains the Prefix expression 
	return s.top();
}

//removes spaces
string spacezap(string input) {
	string addstr = "";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ' ') {
			addstr += input.substr(i, 1);
		}
	}
	return addstr;
}

int main(int argc, char* argv[]) {
	//argument manager stuff
	if (argc < 2) {
		std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << endl;
	}
	ArgumentManager am(argc, argv);		
	ifstream input(am.get("input"));
	ifstream commands(am.get("command"));
	ofstream output(am.get("output"));

	//object declarations
	link list;
	link reserve;

	//some cool variables
	string temp;
	string addin;
	string test;

	//inputs the input, crazy, I know!
	while (getline(input,temp)) {
		if (temp.length() != 0) {
			list.push(spacezap(temp));
		}
	}

	//runs the commands! yay!	
	while (commands >> temp) {
		int pos;
		if (temp == "convertList") {
			commands >> temp;
			string str = temp.substr(1, temp.find(")") - 1);
			list.convertList(str);
		}else
		if (temp == "removeList") {//removelist loop			
			commands >> temp;
			string str = temp.substr(1, temp.find(")") - 1);						
			try {
				int testerino = stoi(str);
				list.pushReserve(to_string(testerino));				
			}
			catch (...) {
				while(1){
					string curr = list.pushReserve(str);
					if (curr == "") {
						break;
					}
				}
			}		
		}else
		if (temp == "printList") {
			cout << list.printList() + "\n\n";
			output << list.printList() + "\n\n";			
		}
		else
		if (temp == "printListBackwards") {
			cout << "Reversed List:\n" + list.printListBackwards(list.getSize()-1)+"\n";
			output << "Reversed List:\n" + list.printListBackwards(list.getSize() - 1) + "\n";
		}else
		if (temp == "pushReserve") {//pushReserveLoop			
			commands >> temp;
			string str = temp.substr(1, temp.find(")")-1);			
			try {
				int testerino = stoi(str);
				string curr = list.pushReserve(to_string(testerino));
				if(curr!="")reserve.push(curr);			
			}
			catch (...) {
				while(1){
					string curr = list.pushReserve(str);
					if (curr == "") {
						break;
					}
					reserve.push(curr);
				}
			}
		}
		else
		if (temp == "popReserve") {
			//popReserve func
			commands >> temp;
			pos = stoi(temp.substr(1, temp.find(")") - 1));
			list.popReserve(reserve.top(), pos);
			reserve.pop();
		}
		else
		if (temp == "flipReserve") {
			link newlink;
			for (int i = reserve.getSize()-1; i >= 0; i--) {
				newlink.push(reserve.get(i));
			}
			reserve = newlink;
		}
		else
		if (temp == "printReserveSize") {
			cout << "Reserve Size: "+to_string(reserve.getSize()) +"\n\n";
			output << "Reserve Size: " + to_string(reserve.getSize()) + "\n\n";
		}
		else
		if(temp=="convertReserve"){
			reserve.convertReserve();
		}
		else
		if(temp=="printReserveTop"){
			cout << "Top of Reserve: " + reserve.top() + "\n\n";
			output << "Top of Reserve: " + reserve.top() + "\n\n";			
		}
		else
		if(temp=="emptyReserve"){//emptyreserveloop			
			commands >> temp;
			pos = stoi(temp.substr(1, temp.find(")") - 1));					
			int revsize = reserve.getSize();
			for (int i = 0; i < revsize; i++) {
				list.popReserve(reserve.top(), pos);
				reserve.pop();
			}
		}		
	}	
}