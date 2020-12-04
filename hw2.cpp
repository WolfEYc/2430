#include <iostream>
#include "ArgumentManager.h"
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <algorithm>
using namespace std;
int sortby;

class LinkedList {
public:
	string id;
	string name;
	string diff;
	LinkedList* next = nullptr;
};

class link {
private:
	LinkedList* head = new LinkedList;
	int size = 0;
	
public:	
	void addnode(string, string, string);
	void print();
};

void link::addnode(string problem_id, string problem_name, string difficulty) {
	LinkedList* tmp = new LinkedList;
	LinkedList* current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	tmp->id = problem_id;
	tmp->name = problem_name;
	tmp->diff = difficulty;	
	current->next = tmp;
	size++;
}

void link::print() {
	LinkedList* current;
	current = head;
	while (current != nullptr) {		
		cout << current->id << "\t" << current->name << "\t" << current->diff << endl;
		current = current->next;
	}
}

struct list {
	string id;
	string name;
	string diff;
	bool operator< (const list& a) const
	{
		if (sortby == 0) {
			return (id < a.id);
		}
		if (sortby == 1) {
			return (name < a.name);
		}		
		if (sortby == 3) {
			return (id > a.id);
		}
		if (sortby == 4) {
			return (name > a.name);
		}		
		return false;
	}
};


int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << std::endl;
	}
	ArgumentManager am(argc, argv);
	string in = am.get("input");
	string com = am.get("command");
	string out = am.get("output");
	ofstream output(out);
	ifstream commands(com);
	ifstream input(in);

	vector<list> problems, templist, emptylist;	
	vector<string> ids;

	//temporary list 
	list addtoprob;
	//temporarily stores a string
	string temp;
	link local;
	//while loop that inputs structs into the linked list
	while (input >> addtoprob.id >> addtoprob.name) {		
		addtoprob.id = addtoprob.id.substr(11,6);
		ids.push_back(addtoprob.id);
		addtoprob.name = addtoprob.name.substr(13);
		while (1 == 1) {
			input >> temp;
			if (temp.substr(0, 11) == "difficulty:") {
				addtoprob.diff = temp.substr(11);
				break;
			}
			addtoprob.name += " "+temp;
		}
		//adds the linked list into my arrays to run seperate functions
		local.addnode(addtoprob.id, addtoprob.name, addtoprob.diff);
		problems.push_back(addtoprob);			
	}
	//local.print();
	bool nexts = false;
	//for fetching commands
	while (!commands.eof()) {
		if (nexts == false) {
			commands >> temp;
		}
		nexts = false;

		
		//add
		if (temp == "add") {
			//gets the index
			string index_str;
			commands >> index_str;			
			int index = stoi(index_str.substr(4));
			commands >> addtoprob.id >> addtoprob.name;
			addtoprob.id = addtoprob.id.substr(11, 6);			
			addtoprob.name = addtoprob.name.substr(13);

			while (1 == 1) {
				commands >> temp;
				if (temp.substr(0, 11) == "difficulty:") {
					addtoprob.diff = temp.substr(11);;
					break;
				}
				addtoprob.name += " " + temp;
			}			
			//adds to the Linked List
				if (find(ids.begin(), ids.end(), addtoprob.id) != ids.end())continue;
				if (index < 0) {
					problems.insert(problems.begin(), addtoprob);
					ids.push_back(addtoprob.id);
					continue;
				}
				if (index > problems.size()) {
					problems.push_back(addtoprob);
					ids.push_back(addtoprob.id);
					continue;
				}
				problems.insert(problems.begin()+index, addtoprob);
				ids.push_back(addtoprob.id);
				continue;
		}	

		//remove function
		if (temp == "remove") {
			commands >> temp;
			if (temp.length() <= 5) {
				int pos = stoi(temp.substr(4));
				if (pos >= problems.size())continue;
				ids.erase(ids.begin() + pos);
				problems.erase(problems.begin()+pos);
				continue;
			}
			if (temp.substr(0, 11) == "difficulty:") {
				temp = temp.substr(11);
				for (int i = 0; i < problems.size(); i++) {
					if (problems[i].diff == temp) {
						ids.erase(ids.begin() + i);
						problems.erase(problems.begin() + i);
						i--;
					}
				}
				continue;
			}
			if (temp.substr(0, 11) == "problem_id:") {
				temp = temp.substr(11,6);
				for (int i = 0; i < problems.size(); i++) {
					if (problems[i].id == temp) {
						ids.erase(ids.begin() + i);
						problems.erase(problems.begin() + i);
						i--;
					}
				}
				continue;
			}
			string addin = temp;
			while (temp != "sort" && temp != "add" && temp != "remove" && !commands.eof()) {
				commands >> temp;
				if (temp != "sort" && temp != "add" && temp != "remove" && !commands.eof()) {
					addin += " " + temp;					
				}
			}
			nexts = true;
			addin = addin.substr(13);
			addin += ",";
			for (int i = 0; i < problems.size(); i++) {
				if (problems[i].name == addin) {
					ids.erase(ids.begin() + i);
					problems.erase(problems.begin() + i);
					i--;
				}
			}
			continue;
		}

		//sort
		if (temp == "sort") {
			commands >> temp;
			//0 if increasing id
			//1 if increasing name
			//2 if increasing diff
			//3 if decreasing id
			//4 if decreasing name
			//5 if decreasing diff

			//runs if by id
			if (temp == "problem_id") {
				commands >> temp;							
				sortby = 0;
				//puts in reverse if decreasing
				if (temp != "increasing")sortby = 3;
				std::sort(problems.begin(), problems.end());
				continue;
			}
			//runs if by name
			if (temp == "problem_name") {
				commands >> temp;				
				sortby = 1;
				//puts in reverse if decreasing
				if (temp != "increasing")sortby = 4;				
				std::sort(problems.begin(), problems.end());
				continue;
			}
			//runs if diff						
				commands >> temp;				
				//puts in reverse if decreasing				
				if (temp == "increasing") {
					for (int i = 0; i < problems.size(); i++) if (problems[i].diff == "Easy")templist.push_back(problems[i]);					
					for (int i = 0; i < problems.size(); i++) if (problems[i].diff == "Medium")templist.push_back(problems[i]);
					for (int i = 0; i < problems.size(); i++) if (problems[i].diff == "Hard")templist.push_back(problems[i]);					
					problems = templist;
					templist = emptylist;
					continue;
				}
				for (int i = 0; i < problems.size(); i++) if (problems[i].diff == "Hard")templist.push_back(problems[i]);
				for (int i = 0; i < problems.size(); i++) if (problems[i].diff == "Medium")templist.push_back(problems[i]);
				for (int i = 0; i < problems.size(); i++) if (problems[i].diff == "Easy")templist.push_back(problems[i]);
				problems = templist;
				templist = emptylist;
				continue;			
		}
	}
	for (int i = 0; i < problems.size(); i++) {
		output << "problem_id:" + problems[i].id + ", problem_name:" + problems[i].name + " difficulty:" + problems[i].diff << "\n";
	}
	return 0;
}