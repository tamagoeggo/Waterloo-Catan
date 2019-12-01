#ifndef _CRITERION_H_
#define _CRITERION_H_

#include <memory>
#include <string>
#include "subject.h"
#include "completion.h"
#include "state.h"
#include "student.h"

class Goal;

class Criterion : public Subject { // Vertex
	int coordinate;
	Student *occupiedBy;
	Completion type = Completion::None; // default is none
	vector<Goal *> goals;
	vector<Criterion *> neighbors;
	public:
	Criterion(int coordinate); // ctor
	void updateOccupant(Student *); // updates occupiedBy
	std::string getStudent();
	void upgrade(); // upgrades the completion of criterion
	State getState() override; // overrides subject function
	int getCoordinate(); // can be used for printing
	void addGoal(Goal *g);
	void addNeighbor(); // adding neighbor from goal
};


#ifndef
