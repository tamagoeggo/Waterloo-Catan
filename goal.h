#ifndef _GOAL_H_
#define _GOAL_H_

#include <memory>
#include <string>
#include "state.h"
#include "student.h"
#include "subject.h"

class Criterion;

class Goal : public Subject { // Road
	int coordinate;
	Student *occupiedBy = nullptr;
	std::vector<Criterion *> neighbors;
	public:
	Goal(int coordinate); // ctor
//	~Goal(); // dtor
	void updateOccupant(Student *); // updates occupiedBy
	Student *getStudent();
	State getState() override; // overrides subject function
	int getCoordinate(); // can be used for printing
	std::vector<Criterion *> getNeighbors(); // to help criterion
	void addNeighbor(Criterion *c);
	bool canPlayerAchieveGoal(Student *s); // to check if Student s owns any of the neighbor
};


#endif
