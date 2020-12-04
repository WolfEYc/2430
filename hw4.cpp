#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <fstream>
using namespace std;
struct node {
	int pnum=0; //the number of the proccess
	int extime=0; //the time it takes that does not change
	int currtime=0; //the time it takes that will iterate down to 0 eventually
	int wait=0; // the time spent not done or not being procceced
	int start=-1; // the time the proc gets started for the first time
	int proc=0; //0 if not being proccesed 1 if being procceced 3 if done	
	int serverits = 0; // how much time spending in server	
	node* next = nullptr;
};
class queue {
private: 
	node* head = new node; //head node points to first node style
	int time = 0; //the time iteration to keep track of
	int servers=0; //how many servers
	int servtime=0; //how much time each proc can be in serv
public:// stuff in queue
	void setServ(int servs, int servertime) { servers = servs; servtime = servertime; }//constructs the server info
	int size() {//returns size
		node* curr = head;
		int count = 0;
		while (curr->next != nullptr) {
			curr = curr->next;
			count++;
		}
		return count;
	}
	bool allproc() {
		node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
			if (curr->proc == 0)return false;
		}
		return true;
	}
	bool freeServer() {//returns true if there is a "server" free or not
		node* curr = head;
		int count = 0;
		while (curr->next != nullptr) {
			curr = curr->next;
			if (curr->proc == 1)count++;
		}
		return count < servers;
	}
	void pushNew(int extime) {//adds new node to end with new data
		node* curr = head;
		node* newnode = new node;
		newnode->extime = extime;
		newnode->currtime = extime;
		newnode->pnum = size() + 1;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = newnode;
	}
	void pushAt(int pos) {	//function grabs node at pos and slaps it at the end of the list
		if (pos < 0 || pos >= size())return;
		node* curr = head;
		node* prev = head;
		node* end = head;
		for (int i = 0; i <= pos; i++) {
			prev = curr;
			curr = curr->next;
		}
		prev->next = curr->next;
		curr->next = nullptr;
		while (end->next != nullptr) {
			end = end->next;
		}
		end->next = curr;
	}
	void fillServs() {
		node* curr = head;
		while (curr->next != nullptr) {//reassigns available servers
			curr = curr->next;
			if (freeServer() && curr->proc == 0) {
				curr->proc = 1;
				if (curr->start == -1)curr->start = time;
			}
		}
	}
	void endTasks() {
		node* curr = head;
		while (curr->next != nullptr) {//checks all the current server procs to see if the procs that are in are done
			curr = curr->next;
			if (curr->currtime == 0 && curr->proc == 1) {
				curr->proc = 3;
			}
		}
	}
	void expireTasks() {
		int pos = 0; //keeps track of position when needed	
		node* curr = head;
		node* prev = head;
		while (curr->next != nullptr) {
			prev = curr;
			curr = curr->next;
			if (servtime == curr->serverits && curr->proc == 1) {//if expired proc will grab and put at end and remove from server
				curr->serverits = 0;
				curr->proc = 0;
				pushAt(pos);
				curr = prev;
			}
			else {
				pos++;//so we dont move when we pushAT to avoid skipping
			}
		}
	}
	void moveTime() {
		time++;//iterates time
		node* curr = head;
		while (curr->next != nullptr) {//iterates the waiting time of all procs not in servers
			curr = curr->next;
			if (curr->proc == 0) {
				curr->wait = curr->wait + 1;
			}
			else if (curr->proc == 1) {
				curr->currtime = curr->currtime - 1;
				curr->serverits = curr->serverits + 1;
			}
		}
	}	
	bool donezo() {//checks if all procs are done
		node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
			if (curr->proc != 3)return false;
		}		
		return true;
	}			
	void sorto() {//jinkies!		
		for (int i = 0; i < size() - 1; i++) {
			node* jorge = head;
			node* juan = head->next;
			node* jose = head->next->next;
			for (int j = 0; j < size() - i - 1; j++) {
				if (jose->pnum < juan->pnum) {//swaps if nessesary
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
	void out(ofstream& output) {//outputs everything
		output << "Max time: " << servtime << endl;
		output << "Number of processes: " << size() << endl;
		output << "Number of servers: " << servers << endl << endl;
		node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
			output << "Process: " << curr->pnum << endl;
			output << "Execution time: " << curr->extime << endl;
			output << "Wait Time: " << curr->wait << endl;
			output << "Start Time: " << curr->start << endl;
			output << "End Time: " << curr->wait + curr->extime << endl << endl;			
		}
	}
};
int main(int argc, char* argv[]) {	
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));	
	ofstream output(am.get("output"));
	queue queueobj;
	int servers, serverits, procs,proctime;
	if(!(input >> serverits >> procs >> servers))return 0;
	queueobj.setServ(servers, serverits);//sets how many servers and how long procs can be in server
	for (int i = 0; i < procs; i++) {//intitial queueing of all procs
		input >> proctime;
		queueobj.pushNew(proctime);
	}		
	while (!queueobj.donezo()) {//will run the iterator untill all procs have been completed
		queueobj.fillServs();//fills up unused servers to proccess first tasks	
		queueobj.endTasks();//will set tasks that are done processing to done mode
		queueobj.expireTasks();//will handle the tasks that have just expired, stops proccessing them and whatnot
		if (!queueobj.freeServer() || queueobj.allproc())queueobj.moveTime();//so at this point check if it is cool to "actually" iterate or "move time"------------------------------------
	}
	queueobj.sorto();//sorts the queue in order of proc num increasing
	queueobj.out(output);//outputs the completed queue
}