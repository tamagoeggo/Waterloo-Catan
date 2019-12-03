#include "goal.h"
#include "criterion.h"
#include "type.h"
using namespace std;

Goal::Goal(int coordinate): coordinate{coordinate} {}

// dtor
Goal::~Goal(){
	occupiedBy = nullptr;
	for(int i = 0; i < this->neighbors.size(); i++){
		delete this->neighbors[i];
	}
}

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

bool Goal::canPlayerAchieveGoal(Student *s) {
	if (neighbors[0]->getStudent() == s) { return true; }
	else if (neighbors[1]->getStudent() == s) { return true; }
	else if (neighbors[0]->goalsOccupancy(s->getPlayer())) { return true; }
	else if (neighbors[1]->goalsOccupancy(s->getPlayer())) { return true; }
	else { return false; }
}
