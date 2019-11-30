#ifndef _STUDENT_H_
#define _STUDENT_H_

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
	string printResources();
	string printGoals();
	string printCriteria();
	void printStatus(); // calls printResources, printGoals, printCriteria
	void trade(Student, Resource, Resource); // trades between 2 students
	int getPoints();
	void stealResources(Student &student);
	void loseResources();
};

#endif
