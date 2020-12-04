#include <iostream>
#include <string>
using namespace std;

struct node {
	string artist;
	string song;
	string alblum;
	node* next = nullptr;
};


class queue {
private: //stuff in the queue
	node head = new node;
	int time = 0;
	int servers;

public:// stuff in queue

	void setServ(int servs) {servers = servs;}

	int size()//returns size

	void push(int input)//adds new node to end with new data

	int grab()//returns the front nodes data and removes it

	bool freeServer()//returns true if there is a "server" free or not

};

int main() {
	playlist thboiz;

	thboiz.push("Micheal Jackson", "Billie Jean", "Thriller");
	thboiz.push("Micheal Jackson", "Thriller", "Thriller");
	thboiz.push("Micheal Jackson", "Beat it", "Thriller");

	thboiz.push("Carly Rae Jepsen", "Call Me Maybe", "One Hit Wonder");
	thboiz.push("Shinedown","Monsters", "Exclaim");

	thboiz.push("Eddie Van Halen", "Jump", "One Night");



	cout << thboiz.Print();

	


	return 0;
}