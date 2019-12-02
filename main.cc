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
  for (int i = 0; i < argc; ++i) {
    cout << argv[i] << "\n";
    if (i > 0 && i % 2 == 0) { // if it is a command line option
    	if (string(argv[i]).compare("-seed") == 0) {
    		try {
    			seed = stoi(argv[i + 1]);
					seed_set = true;
					srand(seed);
    		} catch (...) {
    			cerr << "Missing Seed" << endl;
					seed_set = false;
    		}
    	} else if (string(argv[i]).compare("-load") == 0) {
    		try {
    			load = string(argv[i + 1]);
    		} catch (...) {
    			cerr << "Missing Load File" << endl;
    		}
    	} else if (string(argv[i]).compare("-board") == 0) {
    		try {
    			board = string(argv[i + 1]);
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
	Board b = Board(board);
	b.loadGame(load, &whoseTurn);
	bool rolled = false;
	bool firstAssignment = true;

	while (true) {
		b.print();
		if (whoseTurn == Player::Blue) {
			cout << "Student Blue, where do you want to complete an Assignment?" << endl;
		} else if (whoseTurn == Player::Red) {
			cout << "Student Red, where do you want to complete an Assignment?" << endl;
		} else if (whoseTurn == Player::Orange) {
			cout << "Student Orange, where do you want to complete an Assignment?" << endl;
		} else if (whoseTurn == Player::Yellow) {
			cout << "Student Yellow, where do you want to complete an Assignment?" << endl;
		}
		int placeCriterionAt;
		cin >> placeCriterionAt;
		b.firstCriterion(placeCriterionAt, whoseTurn);
		//int placeGoalAt;
		//cin >> placeGoalAt;
		//b.firstGoal(placeGoalAt, whoseTurn);
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
		if (!rolled) {
			if (whoseTurn == Player::Blue) {
				cout << "Student blue's turn." << endl;
				// status of student
				b.blueStatus();
			} else if (whoseTurn == Player::Red) {
				cout << "Student red's turn." << endl;
				// status of student
				b.redStatus();
			} else if (whoseTurn == Player::Orange) {
				cout << "Student orange's turn." << endl;
				// status of student
				b.orangeStatus();
			} else if (whoseTurn == Player::Yellow) {
				cout << "Student yellow's turn." << endl;
				// status of student
				b.yellowStatus();
			}
			cout << "Choose a dice command: load or fair" << endl;
			cin >> command;
			if (command == "load") {
				b.setDice("load");
			} else if (command == "fair") {
				b.setDice("fair");
			} else {
				cout << "catch statement here" << endl;
			}
			cout << "Roll the dice: roll" << endl;
			cin >> command;
			 if (command == "roll") {
				rolled = true;
				b.roll();
			}
		}
		cout << "help: prints out the list of commands" << endl;

		cin >> command;
		if (command == "board") {
			b.print();
		} else if (command == "status") {
			b.status();
		} else if (command == "criteria") {
			b.criteria(whoseTurn);
		} else if (command == "achieve") { // consider the number
			int goal;
			cin >> goal;
			b.achieveGoal(goal, whoseTurn);
		} else if (command == "complete") {
			int criterion;
			cin >> criterion;
			b.completeCriterion(criterion, whoseTurn);
		} else if (command == "improve") {
			int criterion;
			cin >> criterion;
			b.upgradeCriterion(criterion, whoseTurn);
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
			cout << "||====================================================================================||" << endl;
			cout << "||                                                                                    ||" << endl;
			cout << "||                                    COMMANDS                                        ||" << endl;
			cout << "||                                                                                    ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| board: prints the current board                                                    ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| status: prints the current status of all students in order from student 0 to 3     ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| criteria: prints the criteria the current student has currently completed          ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| achieve <goal\\#>: attempts to achieve the goal at <goal\\#>                         ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| complete <criterion\\#>: attempts to complete the criterion at <criterion\\#>        ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| improve <criterion\\#>: attempts to improve the criterion at <criterion\\#>          ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| trade <colour> <give> <take>: attempts to trade with student <colour> giving one   ||" << endl;
			cout << "||                               resource of type <give> and receiving one resource   ||" << endl;
			cout << "||                               of type <take>                                       ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| next: passes control onto the next student in the game.                            ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| save <file>: saves the current game state to <file>                                ||" << endl;
			cout << "||====================================================================================||" << endl;
			cout << "|| help: prints out the list of commands                                              ||" << endl;
			cout << "||====================================================================================||" << endl;
		}
	}
}
