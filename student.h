#ifndef _STUDENT_H_
#define _STUDENT_H_

class Student {
	Player player; //enum
	map<string, int> resources;
	vector<Criterion*> criteria;
	vector<Goal*> goals;
	public:
	Player getPlayer();
	void updateResources(Resource, int);
	void updateCriterion(Criterion *);
	void updateGoal(Goal *);
	string printResources();
	string printGoals();
	string printCriteria();
	void trade(Student, Resource); // trades between 2 students
	int getPoints();
	void stealResources(Student &student);
	void loseResources();
};

#endif
