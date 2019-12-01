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
