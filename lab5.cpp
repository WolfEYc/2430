#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include <string>
using namespace std;
struct node {
	string data;
	int times=1;
	node* next = nullptr;
};
class mapy {
private:
	node* head = new node;
public:
	int size() {
		node* curr = head;
		int c = 0;
		while (curr->next != nullptr) {
			curr = curr->next;
			c++;
		}
		return c;
	}
	void push(string data) {
		node* curr = head;
		for(int i=0;i<size();i++){
			curr = curr->next;
			if (curr->data == data) {
				curr->times += 1;
				return;
			}				
		}
		node* newnode = new node;
		newnode->data = data;
		curr->next = newnode;
	}
	void sort() {//jinkies!		
		for (int i = 0; i < size() - 1; i++) {
			node* jorge = head;
			node* juan = jorge->next;
			node* jose = juan->next;
			for (int j = 0; j < size() - i - 1; j++) {
				if (jose->data < juan->data) {//swaps if nessesary
					jorge->next = jose;
					juan->next = jose->next;
					jose->next = juan;
					juan = jose;
					jose = jose->next;
				}
				//iterates juan and jose and jorge
				jorge = jorge->next;
				juan = juan->next;
				jose = jose->next;
			}
		}
	}
	void out(ofstream& output) {
		node* curr = head;
		for (int i = 0; i < size(); i++) {
			curr = curr->next;
			output << curr->data << ": " << curr->times << endl;
		}
	}
};
int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream output(am.get("output"));
	mapy bonk;
	string temp;
	int count;
	input >> count;
	for (int i = 0; i < count; i++) {
		input >> temp;
		bonk.push(temp);
	}
	bonk.sort();
	bonk.out(output);
}