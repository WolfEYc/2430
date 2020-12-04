#include <iostream>
#include <string>
using namespace std;

struct node {
	string data;
	node* next = nullptr;
};

class stack {
private:
	node* head = new node;
	int size = 0;
public:
	int getSize() {
		return size;
	}
	void push(string input) {
		node* newnode = new node;
		node* current = head;
		newnode->data = input;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newnode;
		size++;
	}
	string get(int pos) {
		if (pos < 0 || pos >= size)return"";
		node* current = head;
		for (int i = 0; i <= pos; i++) {
			current = current->next;
		}
		return current->data;
	}
	void pop() {
		node* current = head;
		while (current->next->next != nullptr) {
			current = current->next;
		}
		current->next = nullptr;
		size--;
	}
	void flip() {
		node* stopnode = head;
		for (int i = 0; i < size - 1; i++) {
			node* current = head;
			node* prev = head;
			while (current->next != nullptr) {
				prev = current;
				current = current->next;
			}
			current->next = stopnode->next;
			stopnode->next = current;
			stopnode = stopnode->next;
			prev->next = nullptr;
		}
	}
	string print() {
		node* current = head;
		string addstring = "";
		while (current->next != nullptr) {
			current = current->next;
			addstring += current->data + " ";
		}
		return addstring;
	}
	void sort() {
		for (int i = 0; i < size - 1; i++) {
			node* node1 = head->next;
			node* node2 = node1->next;
			for (int j = 0; j < size - i - 1; j++) {
				if (node1->data > node2->data) {
					string temp = node1->data;
					node1->data = node2->data;
					node2->data = temp;
				}
				node1 = node1->next;
				node2 = node2->next;
			}
		}
	}
	void set(int pos, string input) {
		node* current = head;
		if (pos < 0 || pos >= size)return;
		for (int i = 0; i <= pos; i++) {
			current = current->next;
		}
		current->data = input;
	}
	int search(string findata) {
		node* current = head;
		for (int i = 0; i < size; i++) {
			current = current->next;
			if (current->data == findata) {
				return i;
			}
		}
		return -1;
	}
	void setSize(int length) {
		for (int i = size; i < length; i++) {
			push("");
		}
	}
};

struct stacknode {
	stack index;
	stacknode* next = nullptr;
};

class doublestack {
private:
	stacknode* head = new stacknode;
	int size = 0;
public:
	void push(stack input) {
		stacknode* newnode = new stacknode;
		stacknode* current = head;
		newnode->index = input;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newnode;
		size++;
	}
	int getSize() {
		return size;
	}
	string get(int row,int col) {
		stacknode* current = head;
		if (row >= size)return "";
		for (int r = 0; r <= row; r++) {
			current = current->next;
		}		
		return current->index.get(col);
	}
	string print() {
		stacknode* current = head;
		string addstring = "";		
		while (current->next != nullptr) {
			current = current->next;
			addstring += current->index.print() +"\n";
		}
		return addstring;
	}
	void set(int row,int col, string input) {
		stacknode* current = head;
		if (row < 0 || row >= size)return;
		for (int r = 0; r <= row; r++) {
			current = current->next;
		}
		current->index.set(col, input);
	}
	void setSize(int row,int col) {
	    stack emptystack;		
		for (int c = 0; c < col; c++) {
			emptystack.push("");
		}
		for (int r = 0; r < row; r++) {
			push(emptystack);
		}
	}
	int getColSize() {
		return head->next->index.getSize();
	}
};


int letterDistance(string str1, string str2) {
	if (str1.length() == 0 || str2.length() == 0)
		return abs(int(str1.length() - str2.length()));
	return abs(str1[0] - str2[0]) + letterDistance(str1.substr(1), str2.substr(1));
}


int main() {

	stack beans;
	doublestack kek;
	doublestack clean;

	beans.push("mother");
	beans.push("brother");
	beans.push("sister");
	beans.push("father");
	beans.push("deans");
	beans.push("beans");
	

	cout<<beans.print();
	kek.push(beans);


	beans.flip();
	cout << endl;
	cout <<beans.print();

	kek.push(beans);

	beans.pop();
	cout << endl;
	cout<<beans.print();

	kek.push(beans);

	beans.sort();
	cout << endl;
	cout << beans.print();
	cout << endl;
	cout << beans.getSize();
	
	kek.push(beans);

	cout << endl;
	cout << beans.get(0);
	cout << endl;
	cout << beans.search("mother");
	beans.setSize(6);
	cout << endl;
	cout << beans.getSize();
	cout << endl;
	cout << beans.get(5);
	beans.set(5, "gay");
	cout << endl;
	cout << beans.get(10);

	kek.push(beans);

	cout <<kek.print();
	cout << endl;
	cout << kek.get(5,5);
	kek.set(4, 5, "nah");
	cout << endl;
	cout << kek.print();
	cout << endl;

	clean.setSize(5, 6);
	cout << clean.getSize();
	cout << clean.getColSize();

	for (int r = 0;r < clean.getSize(); r++) {
		for (int c = 0; c < clean.getColSize(); c++) {
			clean.set(r, c, to_string(r * c));
		}
	}

	cout << clean.print();
	cout << endl;
	
	

	return 0;
}