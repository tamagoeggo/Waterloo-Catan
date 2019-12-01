#include "goal.h"
#include "criterion.h"
#include "type.h"
using namespace std;

Goal::Goal(int coordinate): coordinate{coordinate} {}

void Goal::updateOccupant(Student *newOccupant) {
	occupiedBy = move(newOccupant);
}

Student *Goal::getStudent() {
	return occupiedBy; // verify and what happens if there's no students
}

State Goal::getState() {
	State state = State{occupiedBy->getPlayer(), Type::Achievement, coordinate};
	return state;
}

int Goal::getCoordinate() {
	return coordinate;
}

vector<Criterion *> Goal::getNeighbors() {
	return neighbors;
}

void Goal::addNeighbor(Criterion *c) {
	neighbors.emplace_back(c);
	c->addGoal(this);
}
