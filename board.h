#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include <memory>
#include <vector>
#include <string>
#include "tile.h"
#include "criterion.h"
#include "goal.h"
#include "student.h"
#include "textdisplay.h"
#include "player.h"
#include "resource.h"
#include "fair.h"
#include "loaded.h"

class Tile;
class Criterion;
class Goal;
class Student;
class TextDisplay;
enum class Player;
enum class Resource;

class Board {
	std::vector<std::unique_ptr<Tile>> tiles;
	std::vector<std::unique_ptr<Criterion>> criterion; // need for putting down criteria
	std::vector<std::unique_ptr<Goal>> goals; // need for putting down goals
	std::vector<std::unique_ptr<Student>> students;
	std::unique_ptr<TextDisplay> td = nullptr;  // to call textdisplay to update it and notify it
	std::string dice = "fair";
	int geeseAt = -1;
	public:

	Board(std::string board, int layer = 2); // ctor with randomized resources and value, init textdisplay

	/*
	Board(const Board&) = delete; // disable copy ctor
  Board& operator=(const Board&) = delete; // disable copy assignment
  ~Board() = default;
	*/

	void completeCriterion(const int coordinate, Player player); // places criteria(similar to setPiece in a4q4) second turn onward
	void firstCriterion(const int coordinate, Player player);
	void upgradeCriterion(const int coordinate, Player player);

	void achieveGoal(const int coordinate, Player player); // places goals(similar to setPiece in a4q4)
	void firstGoal(const int coordinate, Player player);

	void loseResourcesGeese(); // function called if 7 is rolled
	void moveGeese(int coordinates); // moves geese to new tile
	Player whoWon();
	void Reset(); // called when "playagain" is called, resets all player data

	void saveGame(Player curTurn); // takes in current player turn to save for next time
	void saveGameEof(Player curTurn, std::string name); // save game version called when eof
	void loadGame(std::string loadFile, Player *whoseTurn);

	// constructs goals and criterions (coordinates) in vec of vec
	void rowSetup(const int n, std::vector<std::vector<std::unique_ptr<Criterion>>> &criterion, std::vector<std::vector<std::unique_ptr<Goal>>> &goal); // DONE
	// adds goals to criterion and adds neighbors to goals
	void update(const int n, std::vector<std::vector<std::unique_ptr<Criterion>>> &criterion, std::vector<std::vector<std::unique_ptr<Goal>>> &goal); // DONE
	void setDice(std::string type); // DONE
	void roll(Player curTurn);
	void print(); // DONE
	std::string savePrint();
	void status(); // DONE
	void blueStatus();
	void redStatus();
	void orangeStatus();
	void yellowStatus();
	void criteria(Player player); // DONE
	void trade(Player tradeFrom, Player tradeWith, Resource give, Resource take); // DONE
	void criterionAdderHelper(int &iter, const int tileNo); 	// helper function for addCriterion
	void updateCriterionsInTile(const int n); 			// adding the Criterions for a board with n layer(s)i
	void updateCriterionsNeighbor(); // adds neighbors to the criterions (takes in normal vector)

};



#endif
