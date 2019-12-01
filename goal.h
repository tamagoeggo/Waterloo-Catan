#ifndef _GOAL_H_
#define _GOAL_H_

#include <memory>
#include <string>
#include "state.h"
#include "student.h"

class Criterion;

class Goal : public Subject { // Road
	int coordinate;
	Student *occupiedBy = nullptr;
	vector<Criterion *> neighbors;
	public:
	Goal(int coordinate); // ctor
	void updateOccupant(Student *); // updates occupiedBy
	Student *getStudent();
	State getState() override; // overrides subject function
	int getCoordinate(); // can be used for printing
	std::vector<Criterion *> getNeighbors(); // to help criterion
	void addNeighbor(Criterion *c);
};


#endif
