#ifndef _BOARD_H_
#define _BOARD_H_

class Board {
	vector<unique_ptr<Tile>> tiles;
	vector<unique_ptr<Criterion>> criterion; // need for putting down criteria
	vector<unique_ptr<Goal>> goals; // need for putting down goals
	vector<unique_ptr<Student>> students;
	unique_ptr<TextDisplay> td = nullptr;  // to call textdisplay to update it and notify it
	Dice dice; // dice
	public:

	Board(int seed, string board, int layer = 2); // ctor with randomized resources and value, init textdisplay

	void placeCriterion(int coordinate, Player player); // places criteria(similar to setPiece in a4q4)
	void placeGoal(int coordinate, Player player); // places goals(similar to setPiece in a4q4)
	void upgradeCriterion(int coordinate, Player player);

	void moveGeese(int coordinates); // look at assignment specifications for what moving a goose means
	Player whoWon();
	std::string printStudent(Student); // method used for save and load
	void saveGame(Player curTurn); // takes in current player turn to save for next time

	void loadGame(string loadFile);

	// constructs goals and criterions (coordinates) in vec of vec
	void rowSetup(const int layer, vector<vector<Criterion *>> &criterion, vector<vector<Goal *>> &goal); // DONE
	// adds goals to criterion and adds neighbors to goals
	void update(const int layer, vector<vector<Criterion *>> &criterion, vector<vector<Goal *>> &goal); // DONE

	void setDice(string type); // DONE
	void roll(); // DONE
	void print(); // DONE
	void status(); // DONE
	void criteria(Player player); // DONE
	void trade(Player tradeFrom, Player tradeWith, Resource give, Resource take); // DONE

	void criterionAdderHelper(int &iter, const int tileNo); 	// helper function for addCriterion
	void updateCriterionsInTile(const int n); 			// adding the Criterions for a board with n layer(s)i
	void updateCriterionsNeighbor(); // adds neighbors to the criterions (takes in normal vector)

};



#endif
