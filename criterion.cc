#include "criterion.h"
#include "goal.h"
using namespace std;

Criterion::Criterion(int coordinate):coordinate{coordinate} {
	// init goals
	// init neighbors
}

void Criterion::updateOccupant(unique_ptr<Student> newOccupant) {
	occupiedBy = move(newOccupant);
	this->upgrade();
}

string Criterion::getStudent() {
	return occupiedBy->getStudent();	// verify getStudent or getPlayer and what happens if there's no student
}

void Criterion::upgrade() {
	if (this->type == Completion::None) {
		type = Completion::Assignment;
	} else if (this->type == Completion::Assignment) {
		type = Completion::Midterm;
	} else if (this->type == Completion::Midterm) {
		type = Completion::Exam;
	}
}

State Criterion::getState() {
	State state = State{occupiedBy->getStudent(), // verify getStudent or getPlayer
											type, coordinate};
	return state;
}

int Criterion::getCoordinate() {
	return coordinate;
}

void Criterion::addGoal(Goal *g) {
	goals.emplace_back(g);
}

void Criterion::addNeighbor(Criterion *c) {
	neighbors.emplace_back(c);
}
