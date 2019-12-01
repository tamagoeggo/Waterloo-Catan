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

void Criterion::sendResources(Resource resource) {
	if (type == Completion::Assignment) {
		occupiedBy->updateResources(resource, 1);
	}
	else if (type == Completion::Midterm) {
		occupiedBy->updateResources(resource, 2);
	}
	else if (type == Completion::Exam) {
		occupiedBy->updateResources(resource, 3);
	}
	else {
		cout << "Throw an exception here" << endl;
	}
}

void Criterion::upgrade() {
	if (this->type == Completion::None) {
		type = Completion::Assignment;
	} else if (this->type == Completion::Assignment) {
		type = Completion::Midterm;
	} else if (this->type == Completion::Midterm) {
		type = Completion::Exam;
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
		if (goals[i]->getStudent()->getPlayer() == player) return true;
	}
	return false;
}