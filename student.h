#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include <algorithm>    // std::random_shuffle
#include <ctime>
#include <cstdlib>      // std::rand, std::srand
#include <map>
#include <vector>
#include "player.h"
#include "resource.h"
#include "type.h"
#include "state.h"

class Criterion;
class Goal;

class Student {
	Player player; //enum
	std::map<Resource, int> resources;
	std::vector<Criterion*> criteria;
	std::vector<Goal*> goals;
	public:
	//ctor
	Student(Player);
	Player getPlayer();
	void updateResources(Resource, int);
	void updateCriterion(Criterion *);
	void updateGoal(Goal *);

	int numResources(); // returns total number of resources
	std::string returnResources(); // for saving file
	std::string returnGoals(); // for saving file
	std::string returnCriteria(); // for saving file
	std::string printStudent(); // calls returnResources, returnGoals, returnCriteria

	std::string printResources();
	//std::string printGoals();
	std::string printCriteria();
	void printStatus(); // calls printResources, printCriteria for 2.7
	void trade(Student *, Resource, Resource); // trades between 2 students
	void trade(Resource, Resource); // trades with the bank
	int getPoints();
	void stealResources(Student &student);
	void loseResources();
	void Reset(); // resets student data

	bool resourcesCheck(Type type); // returns true if student owns the necessary resources to complete criterion
	void resourcesSpent(Type type); // decreases the amount of resources owned depending on the type of criterion completed
};

#endif
