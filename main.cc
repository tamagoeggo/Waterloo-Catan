#include <iostream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <fstream>
#include <sstream>
#include <memory>
#include "grid.h"
#include "loaded.h"
#include "fair.h"
#include "board.h"
#include "criterion.h"
#include "dice.h"
#include "goal.h"
#include "observer.h"
#include "student.h"
#include "subject.h"
#include "textdisplay.h"

int main(int argc, char* argv[]) {
	// Variable setting
	int seed = 133436;
	int turn_count = 0;
//	shared_ptr<Grid> game(new Grid());
	string save;
	string board;

	// Command Line Argument reading
	for (int i = 0; i < argc; i++) {
		string cd = argv[i];
		stringstream ss;
		if (cd == "-graphic"){
				game_graphic = true;
				game->graphic(game_graphic);
		}
		if (i + 1 != argc) {
			if (cd == "-seed") {
				ss << argv[i + 1];
				ss >> seed;
				//cerr << "seed set" << endl;
		} // seed
			else if (cd == "-load") {
				ss << argv[i + 1];
				ss >> save;
				ifstream file(save);
				if (file.fail()) {
					cout << "Fail to Load: " << save << endl;
					cout << "Reading Input from Screen" << endl;
					continue;
				}
				skip_init = true;
				for (int i = 0; i < 6; i++) {
					if (i == 0) {
						file >> turn_count;
						continue;
					}
					else if (i >= 1 && i <= 4) {
						string sline;
						int caff = -1;
						int lab = -1;
						int lect = -1;
						int stud = -1;
						int tuto = -1;
						int loca = -1;
						int val = -1;
						file >> caff;
						file >> lab;
						file >> lect;
						file >> stud;
						file >> tuto;
						//					cout << caff << " " << lab << " "<< lect << " "<< stud << " "<< tuto << endl;
						game->loading_resources(caff, lab, lect, stud, tuto, i - 1);
						file >> loca;
						if (file.fail()) {
							file.clear();
							file.ignore();
							while (file >> loca) {
								game->loading_goal(loca, i - 1);
							}
						}
						file.clear();
						file.ignore();
						getline(file, sline);
						stringstream sst(sline);
						while (sst >> loca) {
							if (sst >> val) {
								game->loading_crit(loca, val, i - 1);
							}
							else { break; }
						}
						continue;
					}
					else {
						string sline;
						int v = -1;
						int t = -1;
						getline(file, sline);
						stringstream sst(sline);
						int i = 0;
						while (sst >> t) {
							if (sst >> v) {
								game->loading_board(v, t, i);
								i += 1;
							}
							else { break; }
						}
					}
				}
			}
			else if (cd == "-board") {
				ss << argv[i + 1];
				ss >> board;
				int val = -1;;
				int type = -1;
				ifstream f(board);
				int i = 0;
				while (f >> type) {
					if (f >> val) {
						game->loading_board(val, type, i);
						i += 1;
					}
					else { break; }
				}
			}
		}
	}
	// Game Starting !!!!
	while (1) {
		if (Game_on(game, seed, turn_count, skip_init, game_graphic)) {
			game.reset(new Grid());
		}
		else {
			return 0;
		}
	}
	return 0;
};
