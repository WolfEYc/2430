#include <iostream>
using namespace std;

struct node {
	string data;
	node* next = nullptr;
};

class linkedlist {
private:
	node* head = new node;
	int size = 0;
public:
	void append(string input) {
		node* newnode = new node;
		newnode->data = input;
		node* current = head;
		while (current->next != head) {
			current = current->next;
		}
		current->next = newnode;
		newnode->next = head;
	}


};

int main() {



	return 0;
}