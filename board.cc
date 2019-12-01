#include "board.h"
#include "player.h"
#include "tile.h"
#include "student.h"
#include "resource.h"
#include "textdisplay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include <memory>
using namespace std;

// ctor with randomized resources and value, init textdisplay
Board::Board(int layer){
  srand(time(NULL)); // seed
  vector<vector<Criterion *>> criterionv;
  vector<vector<Goal *>> goalv;
  rowSetup(layer, criterionv, goalv);
  update(layer, criterionv, goalv);

  // init Criterion
  /*for(int i = 0; i <= 53; i++){
    Criterion *crit = new Criterion(i);
    criterion.emplace_back(crit);
  }*/
  size_t total_size{ 0 };
  for (auto const& row: criterionv){
      total_size += row.size();
  }
  criterion.reserve(total_size);
  for (auto const& row: criterionv){
      for (auto const& crit: row){
        criterion.emplace_back(move(crit));
      }
  }

  updateCriterionsNeighbor();

  // init  goals
  /*for(int i = 0; i <= 71; i++){
    Goal *newgoal = new Goal(i);
    goals.emplace_back(newgoal);
  }*/
  size_t total_size{ 0 };
  for (auto const& row: goalv){
      total_size += row.size();
  }
  goals.reserve(total_size);
  for (auto const& row: goalv){
    for(auto const& goal: row){
      goals.emplace_back(move(goal));
    }
  }

  // num = (rand() % (upper – lower + 1)) + lower
  // The board will consist of the following values: one 2, one 12, two 3-6, and two 8-11.
	vector<int> values ={2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12};
  random_shuffle(values.begin(), values.end());
  //  The board consists of the following resources: 3 TUTORIAL, 3 STUDY, 4 CAFFEINE, 4 LAB, 4 LECTURE, and 1 NETFLIX
	vector<Resource> resourcetype = {
		Resource::Tutorial,Resource::Tutorial,Resource::Tutorial,
    Resource::Study,Resource::Study,Resource::Study,
		Resource::Caffeine,Resource::Caffeine,Resource::Caffeine,Resource::Caffeine,
    Resource::Lab,Resource::Lab,Resource::Lab,Resource::Lab,
    Resource::Lecture,Resource::Lecture,Resource::Lecture,Resource::Lecture,
    Resource::Netflix
  };
	random_shuffle(resourcetype.begin(), resourcetype.end());

  // init tiles
  for(int i = 0; i < 19; i++){
    if(resourcetype.front() == Resource::Netflix`){
      Tile *newtile = new Tile(0, resourcetype.front());
    }
    else{
      Tile *newtile = new Tile(values.front(), resourcetype.front());
      values.pop_front();
    }
    resourcetype.pop_front();
    tiles.emplace_back(newtile);
  }

  // The assignments will be chosen by students in the order Blue, Red, Orange, Yellow, Yellow, Orange, Red, Blue.
  // 4.1
  // init students
  Student *newstud = new Student(Player::Blue);
  students.emplace_back(newstud);
  Student *newstud = new Student(Player::Red);
  students.emplace_back(newstud);
  Student *newstud = new Student(Player::Orange);
  students.emplace_back(newstud);
  Student *newstud = new Student(Player::Yellow);
  students.emplace_back(newstud);

  // init TextDisplay
  td = make_unique<TextDisplay>(values, resourcetype);

  // init dice
  dice = Fair();

}

/////////////////// ZACH'S OLD WORK /////////////////////////

string Board::printStudent(Student student) {
	string studentData = "";
	studentData += student.printResources() + " g "
	+ student.printGoals() + " c "
	+ student.printCriteria();
	return studentData;
}


void Board::saveGame(Player curTurn) {
  cout << "Please name your save file:" << endl;
  string name;
  cin >> name;
  ofstream saveFile(name + "txt"); // change this to date and time
	if (saveFile.is_open()) {
		saveFile << curTurn << endl;
		saveFile << printStudent(/*blue student*/) << endl;
		saveFile << printStudent(/*red student*/) << endl;
		saveFile << printStudent(/*orange student*/) << endl;
		saveFile << printStudent(/*yellow student*/) << endl;
		saveFile << printBoard() << endl;
		saveFile << /*geese*/ << endl;
	}
	saveFile.close();
}

// 0 3 1 10 3 5 1 4 5 7 3 10 2 11 0 3 3 8 0 2 0 6 1 8 4 12 1 5 4 11 2 4 4 6 2 9 2 9
//  0 representing CAFFEINE, 1 representing LAB, 2 representing LECTURE, 3 representing STUDY, 4 representing TUTORIAL, and 5 representing NETFLIX

void Board::loadGame() {
	string line;
	ifstream saveFile("example.txt");
	if (saveFile.is_open()) {
		while (getline(saveFile, line)) {
			// do stuff with lines
		}
		saveFile.close();
	}
}

/////////////////// RAFEL'S ALGORITHM /////////////////////////

// fills in an empty vector of vector of criterion and
// a vector of vector goals depending on how many layers there are
// in the board
void Board::rowSetup(const int n, vector<vector<Criterion *>> &criterion, vector<vector<Goal *>> &goal) {
	criterion.resize(8 * n + 5);
	goal.resize(8 * n + 5);

	int patternedRow = (2 * n) + 2;
	int goalNo = 0;
	int criterionNo = 0;
	int k = 1; // horizontal goal counter
	for (int i = 0; i < patternedRow; ++i) {	// first set of special rows
		if (i % 2 == 0) {
			for (int j = 0; j < k; ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
			for (int j = 0; j < (2 * k); ++j) {
				criterion[i].emplace_back(make_unique<Criterion>(criterionNo));
				++criterionNo;
			}
		}
		else {
			for (int j = 0; j < (2 * k); ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
			++k;
		}
	}

	int secondPatternedRow = (6 * n) + 3;
	int temp = n; // number of goal in patternedRow
	for (int i = patternedRow; i < secondPatternedRow; ++i) {
		if (i % 2 == 0) {
			for (int j = 0; j < temp; ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
			if (temp == n) { ++temp; }
			else { --temp; }
			for (int j = 0; j < ((2 * n) + 2); ++j) {
				criterion[i].emplace_back(make_unique<Criterion>(criterionNo));
				++criterionNo;
			}
		}
		else {
			for (int j = 0; j < ((2 * n) + 2); ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
		}
	}

	--k; // horizontal goal counter
	for (int i = secondPatternedRow; i < (8 * n) + 5; ++i) {
		if (i % 2 != 0) {
			for (int j = 0; j < (2 * k); ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
		}
		else {
			for (int j = 0; j < k; ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
			for (int j = 0; j < (2 * k); ++j) {
				criterion[i].emplace_back(make_unique<Criterion>(criterionNo));
				++criterionNo;
			}
			--k;
		}
	}
}

// updates all the criterion and goal vector of vectors with their
// fields that require pointers to other criterion or goals
void Board::update(const int n, vector<vector<Criterion *>> &criterion, vector<vector<Goal *>> &goal) {
	int patternedRow = (2 * n) + 2;

	int goalCounter = 1;
	for (int i = 0; i < patternedRow; ++i) {
		if (i % 2 == 0) {
			int c = 0;
			for (int g = 0; g < goalCounter; ++g) { // traversing through the goals in row i
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
			}
			++goalCounter;
		}
		else {
			//adding the first criterion to goal
			int size = goal[i].size();
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g]);
				//cout << criterion[i + 1][g + 1]->getCoordinate() << endl;
				if (i == patternedRow - 1) {
					goal[i][g]->addNeighbor(criterion[i + 1][g]);
				}
				else {
					goal[i][g]->addNeighbor(criterion[i + 1][g + 1]);
				}
			}
		}
	}

	// entering patternedRow
	int secondPatternedRow = (6 * n) + 3;
	for (int i = patternedRow; i <= secondPatternedRow; ++i) {
		int size = goal[i].size();
		if (i % 2 == 0) {
			if (size == n) {
				int cCounter = 1;
				for (int g = 0; g < size; ++g) {
					goal[i][g]->addNeighbor(criterion[i][cCounter]);
					++cCounter;
					goal[i][g]->addNeighbor(criterion[i][cCounter]);
					++cCounter;
				}
			}
			else {
				int cCounter = 0;
				for (int g = 0; g < size; ++g) {
					goal[i][g]->addNeighbor(criterion[i][cCounter]);
					++cCounter;
					goal[i][g]->addNeighbor(criterion[i][cCounter]);
					++cCounter;
				}
			}
		}
		else {
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g]);
				goal[i][g]->addNeighbor(criterion[i + 1][g]);
			}
		}
	}

	int gCounter = n + 1;
	for (int i = secondPatternedRow + 1; i < (8 * n) + 5; ++i) {
		int size = goal[i].size();
		if (i % 2 == 0) {
			int c = 0;
			for (int g = 0; g < gCounter; ++g) {
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
			}
			--gCounter;
		}
		else {
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g + 1]);
				goal[i][g]->addNeighbor(criterion[i + 1][g]);
			}
		}
	}
}

Board::setDice(string type) {
	if (type == "load") {
		int toLoad;
		while (true) {
			cout << "Input a roll between 2 and 12:" << endl;
			cin >> toLoad;
			if (toLoad < 2 || toLoad > 12) {
				cout << "Invalid roll." << endl;
				continue;
			}
			break;
		}
		this->dice = Loaded(toLoad);
	} else if (type == "fair") {
		this->dice = Fair();
	}
}

Board::roll() {
	dice.roll();
}

Board::print() {
	cout << *td;
}

Board::status() {
	for (auto student: students) {
		student.printStatus(); // check with student class
	}
}

Board::criteria(Player player) {
	int toPrint;
	if (player == Player::Blue) {
		toPrint = 0;
	} else if (player == Player::Red) {
		toPrint = 1;
	} else if (player == Player::Orange) {
		toPrint = 2;
	} else { // player == Player::Yellow
		toPrint = 3;
	}
	this->students[toPrint].printCriteria(); // check with student class
}

Board::trade(Player tradeFrom, Player tradeWith, Resource give, Resource take) {
	Student *player1;
	Student *player2;
	if (tradeFrom == Player::Blue) {
		player1 = this->students[0];
	} else if (tradeFrom == Player::Red) {
		player1 = this->students[1];
	} else if (tradeFrom == Player::Orange) {
		player1 = this->students[2];
	} else { // player == Player::Yellow
		player1 = this->students[3];
	}
	if (tradeWith == Player::Blue) {
		player2 = this->students[0];
	} else if (tradeWith == Player::Red) {
		player2 = this->students[1];
	} else if (tradeWith == Player::Orange) {
		player2 = this->students[2];
	} else { // player == Player::Yellow
		player2 = this->students[3];
	}
	player1->trade(player2, give, take);
}

void Board::criterionAdderHelper(int &iter, const int tileNo) {
	for (int i = 0; i < 2; ++i) {
		tiles[iter]->addCriterion(criterion[iter]);
		++iter;
	}
}

void Board::updateCriterionsInTile(const int n) {
	int totalTiles = (3 * n * n) + (3 * n) + 1;
	
	int patternStartsAt = (n * (n + 1)) / 2;	// Tile No.
	double secondPattern = ((n * n) / (double)2) + ((3 * n) / (double)2) + 1;
	int two_n = 2 * patternStartsAt;    		// counter
	int two_n2 = 2 * secondPattern + 1; 		// counter
	int start;                          		// counter
	for (int k = 0; k < n + 1; ++k) {			// loop through the rows
		int starting = patternStartsAt;
		if (k != 0) { starting += (2 * n + 1) * k; }
		for (int i = 0; i < 3; ++i) { 			// loop through the columns
			for (int j = 0; j < n + 1; ++j) {	// loop through the tiles in a row k
				criterionAdderHelper(two_n, starting + j);
			}
		}
		two_n -= 2 * n + 2;
		start = starting;
	}
	for (int k = 0; k < n; ++k) {
		int starting = secondPattern;
		if (k != 0) { starting += (2 * n + 1) * k; }
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < n; ++j) {
				criterionAdderHelper(two_n2, starting + j);
			}
			two_n2 += 2;
		}
		two_n2 -= 2 * n + 2;
	}

	// FIRST END CASE
	
	vector<vector<int>> row; // helper top row
	row.resize(n + 1);
	int tileNo = 0;
	for (int k = 0; k < n + 1; ++k) {
		for (int j = 0; j < k + 1; ++j) {
			row[k].emplace_back(tileNo);
			++tileNo;
		}
	}

	int vert = 0;
	for (int k = 0; k < n + 1; ++k) {
		int vert2 = vert + 1;
		if (k == n) {
			int vert3 = vert2 + 1;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) { // row where Pattern starts
				criterionAdderHelper(vert2, *j);
			}
			if (k > 1) {
				for (auto j = row[k - 2].begin(); j != row[k - 2].end(); ++j) {
					criterionAdderHelper(vert3, *j);
				}
				vert3 += 3;
				for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
					criterionAdderHelper(vert3, *j);
				}
				break;
			}
			vert2 += 2;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				criterionAdderHelper(vert2, *j);
			}
			break;
		}
		for (auto j = row[k].begin(); j != row[k].end(); ++j) {
			criterionAdderHelper(vert, *j);
		}
		if (k >= 2) {
			int vert3 = vert2 + 1;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				criterionAdderHelper(vert2, *j);
			}
			for (auto j = row[k - 2].begin(); j != row[k - 2].end(); ++j) {
				criterionAdderHelper(vert3, *j);
			}
		}
		else if (k == 1) {
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				criterionAdderHelper(vert2, *j);
			}
		}
	}

	// SECOND END CASE

	vector<vector<int>> bottomRow; // helper bottom row
	bottomRow.resize(n);
	
	int secondEndCase = start + n + 1;
	int counter = n;
	int start2 = two_n + 1;
	int start3 = start2 + 1;
	for (int k = n - 1; k >= 0; --k) { // fix limit
		for (int j = 0; j < counter; ++j) {
			bottomRow[k].emplace_back(secondEndCase);
			++secondEndCase;
		}
		--counter;
	}
	
	int temp = two_n - (2 * n) - 1;
	for (auto j = bottomRow[n - 1].begin(); j != bottomRow[n - 1].end(); ++j) { // for special end case
		criterionAdderHelper(temp, *j);
		criterionAdderHelper(start2, *j);
	}

	if (n - 2 >= 0) {
		for (auto j = bottomRow[n - 2].begin(); j != bottomRow[n - 2].end(); ++j) { 
			criterionAdderHelper(start3, *j);
		}
	}
	++start2;
	
	int temp2 = start2 + 1; // for k - 1
	for (int k = n - 1; k >= 0; --k) {
		int temp3 = temp2 + 1; // for  k - 2
		for (auto j = bottomRow[k].begin(); j != bottomRow[k].end(); ++j) {
			criterionAdderHelper(start2, *j);
		}		
		if (k - 1 >= 0) {
			for (auto j = bottomRow[k - 1].begin(); j != bottomRow[k - 1].end(); ++j) {
				criterionAdderHelper(temp2, *j);
			}
			if (k - 2 >= 0) {
				for (auto j = bottomRow[k - 2].begin(); j != bottomRow[k - 2].end(); ++j) {
					criterionAdderHelper(temp3, *j);
				}
			}
		}
	}
}

void Board::updateCriterionsNeighbor() {
	int size = criterion.size();
	for (int i = 0; i < size; ++i) {
		criterion[i]->addNeighbor();
	}
}
