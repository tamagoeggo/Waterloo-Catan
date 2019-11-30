#ifndef _BOARD_H_
#define _BOARD_H_

class Board {
	vector<Tile *> tiles;
	vector<Criterion *> criterion; // need for putting down criteria
	vector<Goal *> goals; // need for putting down goals
	vector<Student *> students;
	TextDisplay *td = nullptr;  // to call textdisplay to update it and notify it
	Dice dice; // dice
	public:
	Board(); // ctor with randomized resources and value, init textdisplay
	void placeCriterion(int coordinate); // places criteria(similar to setPiece in a4q4)
	void placeGoal(int coordinate); // places goals(similar to setPiece in a4q4)
	void upgradeCriterion(int coordinate);
	void moveGeese(int coordinates); // look at assignment specifications for what moving a goose means
	Player whoWon();
	void saveGame();
	void loadGame();
};


#endif
