#include "goal.h"
using namespace std;

Goal::Goal() {
	// how are we initializing goal?
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