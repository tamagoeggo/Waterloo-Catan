#include <iostream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <fstream>
#include <sstream>
#include <memory>
#include <ctime> // std::time
#include <cstdlib>  // std::rand, std::srand
#include "board.h"
#include "loaded.h"
#include "fair.h"
#include "resource.h"
#include "player.h"
using namespace std;

int main(int argc, char* argv[]) {
	int seed;
	bool seed_set = false;
	string load = "default";
	string board = "default";
	Board b;
  for (int i = 0; i < argc; ++i) {
    cout << argv[i] << "\n";
    if (i > 0 && i % 2 == 0) { // if it is a command line option
    	if (argv[i] == "-seed") {
    		try {
    			seed = int(argv[i + 1]);
					seed_set = true;
					srand(seed);
    		} catch (...) {
    			cerr << "Missing Seed" << endl;
					seed_set = false;
    		}
    	} else if (argv[i] == "-load") {
    		try {
    			load = argv[i + 1];
    		} catch (...) {
    			cerr << "Missing Load File" << endl;
    		}
    	} else if (argv[i] == "-board") {
    		try {
    			board = argv[i + 1];
    		} catch (...) {
    			cerr << "Missing Board File" << endl;
    		}
    	}
    }
	}
	if(seed_set == false){
		srand(time(NULL));
	}
	Player whoseTurn = Player::Blue;
	b = Board(/*seed, */board);
	b.loadGame(load, &whoseTurn);
	bool rolled = false;
	while (true) {
		bool firstAssignment = true;
		if (whoseTurn == Player::Blue) {
			cout << "Student blue, where do you want to complete an Assignment?" << endl;
		} else if (whoseTurn == Player::Red) {
			cout << "Student red, where do you want to complete an Assignment?" << endl;
		} else if (whoseTurn == Player::Orange) {
			cout << "Student orange, where do you want to complete an Assignment?" << endl;
		} else if (whoseTurn == Player::Yellow) {
			cout << "Student yellow, where do you want to complete an Assignment?" << endl;
		}
		int placeCriterionAt;
		cin >> placeCriterionAt;
		b.firstCriterion(placeCriterionAt);
		int placeGoalAt;
		cin >> placeGoalAt;
		b.placeGoal(placeGoalAt);
		if (firstAssignment) {
			if (whoseTurn == Player::Blue) {
				whoseTurn = Player::Red;
			} else if (whoseTurn == Player::Red) {
				whoseTurn = Player::Orange;
			} else if (whoseTurn == Player::Orange) {
				whoseTurn = Player::Yellow;
			} else if (whoseTurn == Player::Yellow) {
				firstAssignment = false;
				whoseTurn = Player::Yellow;
			}
		} else {
			if (whoseTurn == Player::Blue) {
				b.print();
				break;
			} else if (whoseTurn == Player::Red) {
				whoseTurn = Player::Blue;
			} else if (whoseTurn == Player::Orange) {
				whoseTurn = Player::Red;
			} else if (whoseTurn == Player::Yellow) {
				whoseTurn = Player::Orange;
			}
		}
	}
	while (cin) {
		string command;
		cin >> command;
		if (!rolled) {
			if (whoseTurn == Player::Blue) {
				cout << "Student blue's turn." << endl;
			} else if (whoseTurn == Player::Red) {
				cout << "Student red's turn." << endl;
			} else if (whoseTurn == Player::Orange) {
				cout << "Student orange's turn." << endl;
			} else if (whoseTurn == Player::Yellow) {
				cout << "Student yellow's turn." << endl;
			}
			if (command == "load") {
				b.setDice("load");
			} else if (command == "fair") {
				b.setDice("fair");
			} else if (command == "roll") {
				rolled = true;
				b.roll();
			}
		} else if (command == "board") {
			b.print();
		} else if (command == "status") {
			b.status();
		} else if (command == "criteria") {
			b.criteria(whoseTurn);
		} else if (command == "achieve") { // consider the number
			int goal;
			cin >> goal;
			b.placeGoal(goal, whoseTurn);
		} else if (command == "complete") {
			int criterion;
			cin >> criterion;
			b.completeCriterion(criterion, whoseTurn);
		} else if (command == "improve") {
			int criterion;
			cin >> criterion;
			b.improveCriterion(coordinate, whoseTurn);
		} else if (command == "trade") {
			Player tradeWith;
			Resource give;
			Resource take;
			string colourInput;
			string giveInput;
			string takeInput;
			cin >> colourInput;
			cin >> giveInput;
			cin >> takeInput;
			if (colourInput == "blue") {
				tradeWith = Player::Blue;
			} else if (colourInput == "red") {
				tradeWith = Player::Red;
			} else if (colourInput == "orange") {
				tradeWith = Player::Orange;
			} else if (colourInput == "yellow") {
				tradeWith = Player::Yellow;
			} else {
				cerr << "Invalid player." << endl;
				continue;
			}
			if (giveInput == "caffeine") {
				give = Resource::Caffeine;
			} else if (giveInput == "lab") {
				give = Resource::Lab;
			} else if (giveInput == "lecture") {
				give = Resource::Lecture;
			} else if (giveInput == "study") {
				give = Resource::Study;
			} else if (giveInput == "tutorial") {
				give = Resource::Tutorial;
			} else if (giveInput == "netflix") {
				give = Resource::Netflix;
			} else {
				cerr << "Invalid resource to give." << endl;
				continue;
			}
			if (takeInput == "caffeine") {
				take = Resource::Caffeine;
			} else if (takeInput == "lab") {
				take = Resource::Lab;
			} else if (takeInput == "lecture") {
				take = Resource::Lecture;
			} else if (takeInput == "study") {
				take = Resource::Study;
			} else if (takeInput == "tutorial") {
				take = Resource::Tutorial;
			} else if (takeInput == "netflix") {
				take = Resource::Netflix;
			} else {
				cerr << "Invalid resource to take." << endl;
				continue;
			}
			b.trade(whoseTurn, tradeWith, give, take);
		} else if (command == "next") {
			if (whoseTurn == Player::Blue) {
				whoseTurn = Player::Red;
			} else if (whoseTurn == Player::Red) {
				whoseTurn = Player::Orange;
			} else if (whoseTurn == Player::Orange) {
				whoseTurn = Player::Yellow;
			} else if (whoseTurn == Player::Yellow) {
				whoseTurn = Player::Blue;
			}
			rolled = false;
			continue;
		} else if (command == "save") {
			b.saveGame(whoseTurn);
		} else if (command == "help") {
			cout << "Valid commands:" << endl
							<< "board" << endl
							<< "status" << endl
							<< "criteria" << endl
							<< "achieve <goal>" << endl
							<< "complete <criterion>" << endl
							<< "improve <criterion>" << endl
							<< "trade <colour> <give> <take>" << endl
							<< "next" << endl
							<< "save <file>" << endl
							<< "help" << endl;
		}
	}
};

