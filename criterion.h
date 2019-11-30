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
	unique_ptr<Student> occupiedBy;
	Completion type;
	vector<unique_ptr<Goal>> goals;
	vector<unique_ptr<Criterion>> neighbors;
	public:
	Criterion(int coordinate); // ctor
	void updateOccupant(unique_ptr<Student>); // updates occupiedBy
	std::string getStudent();
	void upgrade(); // upgrades the completion of criterion
	State getState() override; // overrides subject function
	int getCoordinate(); // can be used for printing
	void addGoal(Goal *g);
	void addNeighbor(Criterion *c);
};


#ifndef
