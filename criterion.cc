#include "criterion.h"
#include "goal.h"
#include <iostream>
#include <string>
using namespace std;

Criterion::Criterion(int coordinate):coordinate{coordinate} {
	// init goals
	// init neighbors
}

void Criterion::updateOccupant(Student *newOccupant) {
	occupiedBy = move(newOccupant);
	this->upgrade();
}

Student *Criterion::getStudent() {
	return occupiedBy;	// verify getStudent or getPlayer and what happens if there's no student
}

// 3.5.5: sends resources to student and
// prints resource send status according to assignment
// Student <colour> gained:
// followed by the line:
// <numResource> <resourceType>
// for each resource they received from the dice roll.
void Criterion::sendResources(Resource resource) {
	if (type == Type::Assignment) {
		occupiedBy->updateResources(resource, 1);
		cout << 1 << " " << resource << endl;
	}
	else if (type == Type::Midterm) {
		occupiedBy->updateResources(resource, 2);
		cout << 2 << " " << resource << endl;
	}
	else if (type == Type::Exam) {
		occupiedBy->updateResources(resource, 3);
		cout << 3 << " " << resource << endl;
	}
	else {
		throw "Invalid resource";
	}
}

void Criterion::upgrade() {
	if (this->type == Type::None) {
		type = Type::Assignment;
	} else if (this->type == Type::Assignment) {
		type = Type::Midterm;
	} else if (this->type == Type::Midterm) {
		type = Type::Exam;
	}
	else {
		throw "Invalid command; Criterion is already an Exam.";
	}
}

State Criterion::getState() {
	State state = State{occupiedBy->getPlayer(), type, coordinate};
	return state;
}

int Criterion::getCoordinate() {
	return coordinate;
}

void Criterion::addGoal(Goal *g) {
	goals.emplace_back(g);
}

void Criterion::addNeighbor() {
	int size = goals.size();
	for (int i = 0; i < size; ++i) {
		neighbors.emplace_back(goals[i]->getNeighbors()[0]);
		neighbors.emplace_back(goals[i]->getNeighbors()[1]);
	}
}

bool Criterion::areNeighborsUnoccupied() {
	int size = neighbors.size();
	for (int i = 0; i < size; ++i) {
		if (neighbors[i]->getStudent()) return false; // if neighbour is occupied
	}
	return true;
}

bool Criterion::goalsOccupancy(Player player) {
	int size = goals.size();
	for (int i = 0; i < size; ++i) {
		if (!goals[i]->getStudent()) return false;
		if (goals[i]->getStudent()->getPlayer() == player) return true;
	}
	return false;
}
