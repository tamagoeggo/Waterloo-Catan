#ifndef _GOAL_H_
#define _GOAL_H_

#include <memory>
#include <string>
#include "state.h"
#include "student.h"

class Criterion;

class Goal : public Subject { // Road
	int coordinate;
	unique_ptr<Student> occupiedBy;
	vector<unique_ptr<Criterion>> neighbours;
	public:
	Goal(int coordinate); // ctor
	void updateOccupant(unique_ptr<Student>); // updates occupiedBy
	std::string getStudent();
	State getState() override; // overrides subject function
	int getCoordinate(); // can be used for printing
	void addNeighbor(Criterion *c);
};


#endif
