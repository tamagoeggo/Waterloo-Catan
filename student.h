#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "player.h"
#include "resource.h"
#include <map>

class Criterion;
class Goal;

class Student {
	Player player; //enum
	map<Resource, int> resources;
	vector<Criterion*> criteria;
	vector<Goal*> goals;
	public:
	//ctor
	Student(Player);
	Player getPlayer();
	void updateResources(Resource, int);
	void updateCriterion(Criterion *);
	void updateGoal(Goal *);

	std::string returnResources(); // for saving file
	std::string returnGoals(); // for saving file
	std::string returnCriteria(); // for saving file

	std::string printResources();
	//std::string printGoals();
	std::string printCriteria();
	void printStatus(); // calls printResources, printCriteria for 2.7
	void trade(Student, Resource, Resource); // trades between 2 students
	int getPoints();
	void stealResources(Student &student);
	void loseResources();
};

#endif
