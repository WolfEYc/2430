#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

struct node {
	string data;
	node* left = nullptr;
	node* right = nullptr;
};
struct bean {
	int first=-1;
	int second=-1;
};
int binaryToDecimal(int n)
{
	int num = n;
	int dec_value = 0;
	int base = 1;

	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;

		dec_value += last_digit * base;

		base = base * 2;
	}

	return dec_value;
}
int sum(string conv) {
	int c = 0;
	for (int i = 0; i < conv.length(); i++) {
		c += conv[i];
	}
	return c;
}
node* newnode(string input) {
	node* beep = new node;
	beep->data = input;
	return beep;
}
	node* push(node* root,string toAdd) {
		if (root == nullptr) return newnode(toAdd);

		if (sum(toAdd) < sum(root->data)) {
			root->left = push(root->left, toAdd);
		}
		else {
			root->right = push(root->right, toAdd);
		}
		return root;
	}
	void print(node* root) {
		if (root != nullptr) {
			print(root->left);
			print(root->right);
			cout << root->data << " ";
		}
	}
	int getLevelUtil(node* root,string data, int level)
	{
		if (root == nullptr)
			return 0;

		if (root->data == data)
			return level;

		int downlevel = getLevelUtil(root->left,data, level + 1);
		if (downlevel != 0)
			return downlevel;

		return getLevelUtil(root->right,data, level + 1);		
	}		
	int getLevel(node* node, string data)
	{
		return getLevelUtil(node, data, 1);
	}
	bool search(node* root, string value) {
		return (root != nullptr && (root->data == value || search(root->left, value) || search(root->right, value)));
	}
	int size(node* root) {
		if (root == nullptr)return 0;
		return 1 + size(root->left) + size(root->right);
	}	

class hashbean {
private:	
	vector<int> hashtable;
	vector<int> clean;
	int size;
	int shirts;
public:	
	void cuckoo(vector<bean> keys, int sizey) {
		size = sizey;
		shirts = keys.size();
		hashtable = clean;
		for (int i = 0; i < size; i++) {
			hashtable.push_back(-1);
		}		
		for (int i = 0; i < keys.size(); i++) {
			place(keys[i], 0);
		}		
	}	
	void place(bean burrito, int c) {		
		if (c == size)return;
		if (hashtable[burrito.first] != -1)
		{
			bean dis;
			dis.first = hashtable[burrito.first];
			dis.second = burrito.first;
			hashtable[burrito.first] = burrito.second;
			place(dis,c + 1);
		}
		else { //else: place the new key in its position 
			hashtable[burrito.first] = burrito.second;			
		}			
	}
	bool hashable() {
		int count=0;
		cout << "Hashtable: ";
		for (int i = 0; i < size; i++) {
			if (hashtable[i] != -1) {
				cout << hashtable[i] << " ";
				count++;
			}
			else {
				cout << "- ";
			}
		}
		cout << endl;
		return count == shirts;
	}
};

void printy(vector<bean> keys) {
	cout << "UPC Codes: ";
	for (int i = 0; i < keys.size(); i++) {
		cout << keys[i].first <<","<< keys[i].second<< "  ";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {	
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream output(am.get("output"));

	hashbean hashtab;
	int styles,tsize,sty1,sty2,goodamt,tables, skip = 0;
	string temp, query;	
	bool flaggy = 0;

	input >> tables;
	for(int i=0;i<tables;i++){
		input >> styles;
		input >> tsize;
		cout <<"Codes: "<<styles <<endl<< "Table Size: " << tsize << endl;
		vector<bean> keys;
		for (int i = 0; i < styles; i++) {
			input >> sty1>>sty2;
			bean newbean;
			newbean.first = binaryToDecimal(sty1);
			newbean.second = binaryToDecimal(sty2);			
			keys.push_back(newbean);
		}	
		printy(keys);
		hashtab.cuckoo(keys, tsize);
		if (hashtab.hashable()) {
			flaggy = 1;
			goodamt = styles;
			cout << "valid inventory log" << endl;
			output << "valid inventory log" << endl;
		}
		else if(flaggy==0){
			skip += styles;
			cout << "INVALID INVENTORY LOG!!!" << endl;
			output << "INVALID INVENTORY LOG!!!" << endl;
		}
		else {
			cout << "INVALID INVENTORY LOG!!!" << endl;
			output << "INVALID INVENTORY LOG!!!" << endl;
		}		
		cout << endl;
	}	
	cout <<"Styles to skip: " << skip <<endl;
	cout << "Styles to include: " << goodamt <<endl;
	
	input >> query;
	for (int i = 0; i < skip; i++) {
		input >> temp;
	}	
	cout <<"Shirt to Find: "<< query<<endl;	
	input >> temp;
	node* head = newnode(temp);	
	cout <<"Styles added to BST: " << temp;
	for (int i = 0; i < goodamt-1; i++) {
		input >> temp;
		cout <<" "<<temp;
		push(head, temp);
	}
	int levelfound = getLevel(head, query);
	cout <<endl<< "Found at level: " << levelfound << endl;
	output << levelfound;	
}