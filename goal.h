#ifndef _GOAL_H_
#define _GOAL_H_

class Goal : public Subject { // Road
	int coordinate;
	Student *occupiedBy;
	vector<Criterion *> neighbours; 
	public:
	void updateOccupant; // updates occupiedBy
	string getStudent(); 
	Goal(); // ctor
	State getState() override; // overrides subject function
	int getCoordinate(); // can be used for printing
};


#endif
