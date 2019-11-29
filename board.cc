#include "board.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
