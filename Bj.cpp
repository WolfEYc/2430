#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

void hit(vector<int>& players,int pos) {
	if (pos >= 0 && pos < players.size()) {
		players[pos] += rand() % 11 + 1;
	}
}

bool bust(vector<int>& players, int pos) {
	return (pos >= 0 && pos < players.size() && players[pos]>21);	
}

bool doney(vector<bool> list) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == 0)return false;
	}
	return true;
}

bool win(vector<int> players,int pos) {
	if (pos == 0) {
		for (int i = 1; i < players.size(); i++) {
			if(win(players,i))
				return 0;
		}
		return 1;
	}
	if (pos >= 0 && pos < players.size()) {
		return (!bust(players, pos) && (players[pos] > players[0] || bust(players,0)));
	}
}
int main() {
	bool play = true;
	while (play) {
		int amt;
		string choice;
		cout << "How many players?" << endl;
		cin >> amt;
		vector<int> players(amt+1,0);
		vector<bool> done(amt, 0);	
		for (int i = 1; i < players.size(); i++) {
			hit(players, i);
		}
		while (!doney(done)) {
			for (int i = 1; i < players.size(); i++) {				
				cout << "player " << i << ": " << players[i] << endl;
			}
			for (int i = 1; i < players.size(); i++) {
				if (done[i-1]==0) {
					cout << "Player " << i << " hit? y or n"<<endl;					
					cin >> choice;
					if (choice == "y") {
						hit(players, i);
					}
					else {
						done[i-1] = 1;
					}
					if (bust(players, i))
						done[i-1] = 1;
				}
			}			
		}
		while (!bust(players,0) && !win(players, 0)) {
			hit(players, 0);
		}
		for (int i = 0; i < players.size(); i++) {
			if(win(players,i))
				cout << "player " << i << ": " << players[i] << " Win" << endl;
			else
				cout << "player " << i << ": " << players[i] << " Lose" << endl;
		}
		cout << "Play Again? y or n" << endl;
		cin >> choice;
		if (choice == "y")
			play = true;
		else
			play = false;
	}
}