#ifndef _CRITERION_H_
#define _CRITERION_H_

#include <vector>
#include "subject.h"
#include "type.h"
#include "state.h"
#include "student.h"
#include "resource.h"

class Goal;

class Criterion : public Subject { // Vertex
	int coordinate;
	Student *occupiedBy = nullptr;
	Type type = Type::None; // default is none
	std::vector<Goal *> goals;
	std::vector<Criterion *> neighbors;
	public:
	Criterion(int coordinate); // ctor
	~Criterion(); // dtor
	void updateOccupant(Student *newOccupant); // updates occupiedBy
	Student *getStudent();
	void sendResources(Resource resource);
	void upgrade(); // upgrades the completion of criterion
	State getState() override; // overrides subject function
	int getCoordinate(); // can be used for printing
	void addGoal(Goal *g);
	void addNeighbor(); // adding neighbor from goal
	bool areNeighborsUnoccupied(); // returns true when if neighbours are not occupied
	bool goalsOccupancy(Player player, int coordinate = -1); // returns true if player owns any of the goals adjacent
};


#endif
