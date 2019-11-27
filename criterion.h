#ifndef _CRITERION_H_
#define _CRITERION_H_

class Criterion : public Subject { // Vertex
	int coordinate;
	Student *occupiedBy;
	Completion type;
	vector<Goal *> goals;
	vector<Criterion *> neighbors;
	public:
	void updateOccupant; // updates occupiedBy
	string getStudent();
	Criterion(); // ctor 
	void upgrade(); // upgrades the completion of criterion
	State getState() override; // overrides subject function
	int getCoordinate(); // can be used for printing
};


#ifndef
