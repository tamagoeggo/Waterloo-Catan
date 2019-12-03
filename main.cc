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
	cin.exceptions(ios::eofbit);

		bool playagain = true;
		while(playagain){
			cout << "BEGINNING OF PLAYAGAIN LOOP" << endl;
			int seed;
			bool seed_set = false;
			string load = "default";
			string board = "default";

		  for (int i = 0; i < argc; ++i) {
		    cout << argv[i] << "\n";
		    if (i > 0 && i % 2 == 1) { // if it is a command line option
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
			if (load == "default" && board == "default") {}
			else {
				//string resourceList;
				ifstream f;
				int lineNo;
				if (load != "default") {			// it it is a loaded game
					f.open(load + ".txt");
					lineNo = 6;
				} else {					// if it is a game with a set board
					f.open(board + ".txt");
					lineNo = 1;
				}
				for (int i = 1; i <= lineNo; i++) {
					getline(f, board);
				}
			}
			Board b = Board(board);
			b.loadGame(load, &whoseTurn);
			bool rolled = false;
			bool firstAssignment = true;

			try{
				// FIRST PHASE
				if (load == "default") {
					while (true) {
					b.print();
					if (whoseTurn == Player::Blue) {
						cout << "Student Blue, where do you want to complete an Assignment?" << endl;
						cout << ">";
					} else if (whoseTurn == Player::Red) {
						cout << "Student Red, where do you want to complete an Assignment?" << endl;
						cout << ">";
					} else if (whoseTurn == Player::Orange) {
						cout << "Student Orange, where do you want to complete an Assignment?" << endl;
						cout << ">";
					} else if (whoseTurn == Player::Yellow) {
						cout << "Student Yellow, where do you want to complete an Assignment?" << endl;
						cout << ">";
					}

					bool validArg = true;
					while(validArg){
						int placeCriterionAt;
						cin >> placeCriterionAt;
						try{
							b.firstCriterion(placeCriterionAt, whoseTurn);
							validArg = false;
						} catch(char const* msg){
							cout << msg << endl;
							validArg = true;
						}
					}

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
				}
				else {
					b.print();
				}

				// SECOND PHASE
				// First 2 rounds of preliminary moves finished
				string command;
				while (cin) {
					// checking if a player has won
					if(b.whoWon() != Player::None){
						cout << b.whoWon() << " wins!" << endl;
						cout << "Would you like to play again?" << endl;
						cout << ">";
						cin >> command;
						while(command != "yes" && command != "no"){
							cout << "Enter yes or no" << endl;
							cin >> command;
						}
						if(command == "yes"){
							cout << b.whoWon() << endl; // DEBUG STATEMENT
							playagain = true;
							b.Reset(); // resets all player data
							cout << b.whoWon() << endl; // DEBUG STATEMENT
						}
						else if(command == "no"){
							playagain = false;
						}
						break;
					}

					if (!rolled) {
						if (whoseTurn == Player::Blue) {
							cout << "Student Blue's turn." << endl;
							b.blueStatus();
							cout << ">";
						} else if (whoseTurn == Player::Red) {
							cout << "Student Red's turn." << endl;
							b.redStatus();
							cout << ">";
						} else if (whoseTurn == Player::Orange) {
							cout << "Student Orange's turn." << endl;
							b.orangeStatus();
							cout << ">";
						} else if (whoseTurn == Player::Yellow) {
							cout << "Student Yellow's turn." << endl;
							b.yellowStatus();
							cout << ">";
						}
						// choose dice type
						cout << "Choose a dice command: load or fair" << endl;
						cout << ">";
						cin >> command;
						while(command != "load" && command != "fair"){
							cout << "Invalid command" << endl;
							cout << ">";
							cin >> command;
						}
						if (command == "load") {
							b.setDice("load");
						} else if (command == "fair") {
							b.setDice("fair");
						}
						// roll chosen dice
						cout << "Roll the dice: roll" << endl;
						cout << ">";
						cin >> command;
						while(command != "roll"){
							cout << "Invalid command" << endl;
							cout << ">";
							cin >> command;
						}
						if (command == "roll") {
							rolled = true;
							b.roll(whoseTurn); // rolls the dice and sends resources, printing dice roll and resources
						}
					}

					// PHASE 3
					// gameplay 4.3
					cout << "Enter a command." << endl;
					cout << ">";

					cin >> command;
					while(command != "board" && command != "status" && command != "criteria"
								&& command != "achieve" && command != "complete" && command != "improve"
								&& command != "trade" && command != "next" && command != "save"
								&& command != "help"){
						cout << "Invalid command" << endl;
						cout << "(help: prints out the list of commands)" << endl;
						cout << ">";
						cin >> command;
					}
					if (command == "board") {
						b.print();
					}
					else if (command == "status") {
						b.status();
					}
					else if (command == "criteria") {
						b.criteria(whoseTurn);
					}
					else if (command == "achieve") { // consider the number
						int goal;
						cin >> goal;
						try {
							b.achieveGoal(goal, whoseTurn);
						} catch (const char *c) {
							cout << c << endl;
						}
					}
					else if (command == "complete") {
						int criterion;
						cin >> criterion;
						try {
							b.completeCriterion(criterion, whoseTurn);
						} catch (const char *c) {
							cout << c << endl;
						}
					}
					else if (command == "improve") {
						int criterion;
						cin >> criterion;
						try {
							b.upgradeCriterion(criterion, whoseTurn);
						} catch (const char *c) {
							cout << c << endl;
						}
					}
					else if (command == "trade") {
						Player tradeWith;
						Resource give;
						Resource take;
						string colourInput;
						string giveInput;
						string takeInput;
						cin >> colourInput;
						cin >> giveInput;
						cin >> takeInput;
						if (colourInput == "Blue") {
							tradeWith = Player::Blue;
						} else if (colourInput == "Red") {
							tradeWith = Player::Red;
						} else if (colourInput == "Orange") {
							tradeWith = Player::Orange;
						} else if (colourInput == "Yellow") {
							tradeWith = Player::Yellow;
						} else {
							cerr << "Invalid player. Valid players: Blue, Red, Orange, Yellow"<< endl;
							continue;
						}
						if (giveInput == "Caffeine") {
							give = Resource::Caffeine;
						} else if (giveInput == "Lab") {
							give = Resource::Lab;
						} else if (giveInput == "Lecture") {
							give = Resource::Lecture;
						} else if (giveInput == "Study") {
							give = Resource::Study;
						} else if (giveInput == "Tutorial") {
							give = Resource::Tutorial;
						} else {
							cerr << "Invalid resource to give. Valid resources: Caffeine, Lab, Lecture, Study, Tutorial" << endl;
							continue;
						}
						if (takeInput == "Caffeine") {
							take = Resource::Caffeine;
						} else if (takeInput == "Lab") {
							take = Resource::Lab;
						} else if (takeInput == "Lecture") {
							take = Resource::Lecture;
						} else if (takeInput == "Study") {
							take = Resource::Study;
						} else if (takeInput == "Tutorial") {
							take = Resource::Tutorial;
						} else {
							cerr << "Invalid resource to take. Valid resources: Caffeine, Lab, Lecture, Study, Tutorial" << endl;
							continue;
						}
						if(whoseTurn == tradeWith){
							cout << "You cannot trade with yourself." << endl;
							continue;
						}
						b.trade(whoseTurn, tradeWith, give, take);
					}
					// next player turn
					else if (command == "next") {
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
					}
					else if (command == "save") {
						b.saveGame(whoseTurn);
					}
					else if (command == "help") {
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
			// if eof
			catch(...){
				b.saveGameEof(whoseTurn, "backup");
				cout << "Game ended unexpectedly, saving game to backup.txt." << endl;
			}
	}
	return 0;
}
