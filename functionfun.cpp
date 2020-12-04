#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

double pi = 2 * acos(0.0);

int bomb(int n) {
	if (n == 0)return 1;
	return n * bomb(n / 2);
}

int findpy(double a, double b, double c) {
	if (c > 0)return  sqrt(-(a * a) - (b * b) + (c * c));
	return sqrt(a * a + b * b + c * c);
}

struct node {
	int data;
	node* left = nullptr;
	node* right = nullptr;	
};

struct bean{
	string data;
	bean* next = nullptr;
};

int sortadd(bean* root, string input) {
	bean* newbean = new bean;
	newbean->data = input;
	if (root->next == nullptr){
		root->next = newbean;
		return 0;
	}
	else if (input > root->next->data) {
		newbean->next = root->next;
		root->next = newbean;		
		return 0;
	}
	else {		
		return 1+ sortadd(root->next, input);
	}
}

void unsortadd(bean* root, string input) {
	bean* newbean = new bean;
	newbean->data = input;
	if (root->next == nullptr)
		root->next = newbean;
	else
		unsortadd(root->next, input);
}

int size(bean* root) {
	if (root->next == nullptr)return 0;
	return 1 + size(root->next);
}

int bubblesort(bean* root) {
	int c = 0;
	for (int i = 0; i < size(root)-1; i++) {
		bean* juan = root->next;
		bean* jose = juan->next;
		for (int j = 0; j < size(root) - i - 1; j++) {
			if (jose->data > juan->data) {
				string temp = jose->data;
				jose->data = juan->data;
				juan->data = temp;
			}
			juan = juan->next;
			jose = jose->next;
			c++;
		}
	}
	return c;
}

void printy(bean* root) {	
	if (root != nullptr) {
		printy(root->next);
		cout << root->data << " ";
	}
}


class binarytree {
private:
	node* head = new node;
	node* curr = new node;	
	int size = 0;
public:
	void addnode(int input) {
		curr = head;
		node* newnode = new node;
		newnode->data = input;
		while (curr->right != nullptr) {
			curr = curr->right;
			if (curr->data > input) {
				if (curr->left == nullptr) {
					curr->left = newnode;					
					size++;
					//cout <<endl << to_string(input) ;
					return;
				}
				else {
					curr = curr -> left;
				}						
			}
		}
		size++;
		curr->right = newnode;		
		//cout << " "+ to_string(input);
	}

	

	void print(node* root) {
		if (root!=nullptr) {
			print(root->left);
			print(root->right);			
			cout << root->data << " ";
		}
	}

	int add(node* root) {
		if (root == nullptr) {				
			return 0;
		}		
		return root->data + add(root->left) + add(root->right);
	}
	
	bool search(node* root,int value) {
		return (root != nullptr && (root->data == value || search(root->left, value) || search(root->right, value)));
	}

	node* getFirst() {
		return head->right;
	}
	int getSize() {
		return size;
	}
};







int main(int argc, char* argv[]) {
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream output(am.get("output"));
	
	/*binarytree test;
	for (int i = 10; i >= 0 ; i--) {
		test.addnode(i);
		test.addnode(i);
	}

	test.print(test.getFirst());

	cout << test.add(test.getFirst());

	for (int i = 20; i >= 0; i--) {
		cout << i << " ";
		cout << test.search(test.getFirst(), i)<< " ";
	}*/

	//cout << findpy(128.5, 346.78, 0);
	
	bean* head = new bean;
	bean* bhead = new bean;
	int c = 0;
	
	string temp;
	while (input >> temp) {
		c += sortadd(head, temp);
		unsortadd(bhead, temp);
	}
	int benis = bubblesort(bhead);
	cout << c << endl;
	cout << benis << endl;
	printy(head);

	cout << endl<<endl;
	printy(bhead);
	cout << endl;
	return 0;
}