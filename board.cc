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
using namespace std;

// ctor with randomized resources and value, init textdisplay
Board::Board(){
  srand(time(NULL)); // seed
  int x;
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
    if(resourcetype.front() == Resource::Netflix){
      Tile *newtile = new Tile(0, resourcetype.front());
    }
    else{
      Tile *newtile = new Tile(values.front(), resourcetype.front());
      values.pop_front();
    }
    resourcetype.pop_front();
    tiles.emplace_back(newtile);
  }

  // init Criterion
  for(int i = 0; i <= 53; i++){
    Criterion *crit = new Criterion(i);
    criterion.emplace_back(crit);
  }

  // init  goals
  for(int i = 0; i <= 71; i++){
    Goal *newgoal = new Goal(i);
    goals.emplace_back(newgoal);
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
  td = new TextDisplay(values, resourcetype);
}


/////////////////// ZACH'S OLD WORK /////////////////////////
string printStudent(Student student) {
	string studentData = "";
	studentData += student.printResources() + " g "
	+ student.printGoals() + " c "
	+ student.printCriteria();
	return studentData;
}

void save() {
	ofstream saveFile("example.txt"); // change this to date and time
	if (myfile.is_open()) {
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

void load() {
	string line;
	ifstream saveFile("example.txt");
	if (saveFile.is_open()) {
		while (getline(saveFile, line)) {
			// do stuff with lines
		}
		saveFile.close();
	}
}
