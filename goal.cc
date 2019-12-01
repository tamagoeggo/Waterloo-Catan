#include "goal.h"
#include "criterion.h"
using namespace std;

Goal::Goal(int coordinate): coordinate{coordinate} {
	// init neighbors here
}

void Goal::updateOccupant(unique_ptr<Student> newOccupant) {
	occupiedBy = move(newOccupant);
}

string Goal::getStudent() {
	return occupiedBy->getStudent(); // verify and what happens if there's no students
}

State Goal::getState() {
	State state = State{occupiedBy->getStudent(), // verify getStudent or getPlayer
											type, coordinate};
	return state;
}

int Goal::getCoordinate() {
	return coordinate;
}

void Goal::addNeighbor(Criterion *c) {
	neighbors.emplace_back(c);
	c->addGoal(this);
}
