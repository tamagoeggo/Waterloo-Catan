#ifndef _BOARD_H_
#define _BOARD_H_

#include <memory>
#include <vector>
#include "dice.h"

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
	string dice = "fair";
	int geeseAt = -1;
	public:

	Board(/*int seed, string board, */int layer = 2); // ctor with randomized resources and value, init textdisplay


	void completeCriterion(const int coordinate, Player player); // places criteria(similar to setPiece in a4q4) second turn onward
	void firstCriterion(const int coordinate, Player player);
	void upgradeCriterion(const int coordinate, Player player);

	void achieveGoal(const int coordinate, Player player); // places goals(similar to setPiece in a4q4)
	void firstGoal(const int coordinate, Player player);

	void loseResourcesGeese(); // function called if 7 is rolled
	void moveGeese(int coordinates); // moves geese to new tile
	Player whoWon();
	std::string printStudent(Student); // method used for save and load

	void saveGame(Player curTurn); // takes in current player turn to save for next time
	void loadGame(std::string loadFile, Player &whoseTurn);

	// constructs goals and criterions (coordinates) in vec of vec
	void rowSetup(const int layer, std::vector<std::vector<Criterion *>> &criterion, std::vector<std::vector<Goal *>> &goal); // DONE
	// adds goals to criterion and adds neighbors to goals
	void update(const int layer, std::vector<std::vector<Criterion *>> &criterion, std::vector<std::vector<Goal *>> &goal); // DONE
	void setDice(std::string type); // DONE
	void roll();
	void print(); // DONE
	void status(); // DONE
	void criteria(Player player); // DONE
	void trade(Player tradeFrom, Player tradeWith, Resource give, Resource take); // DONE
	void criterionAdderHelper(int &iter, const int tileNo); 	// helper function for addCriterion
	void updateCriterionsInTile(const int n); 			// adding the Criterions for a board with n layer(s)i
	void updateCriterionsNeighbor(); // adds neighbors to the criterions (takes in normal vector)

};



#endif

