#include <iostream>
#include <vector>
#include <array>

using namespace std;

class Goal;

class Criterion { // Vertex
	int coordinate;
	vector<Goal *> goals;
	vector<Criterion *> neighbors;
	public:
	Criterion(int coordinate) : coordinate{coordinate} {}
	~Criterion() {}

	int getCoordinate() { return coordinate; }
	void addGoal(Goal *g) {
		goals.emplace_back(g);
	}
	void addNeighbor(Criterion *c) {
		neighbors.emplace_back(c);
	}
};

class Goal { // Road
	int coordinate;
	vector<Criterion *> neighbors; 
	public:
	Goal(int coordinate) : coordinate{coordinate} {}
	~Goal() {}

	int getCoordinate() { return coordinate; }
	void addNeighbor(Criterion *c) {
		cout << "Adding neighbor to Goal" << endl;
		neighbors.emplace_back(c);
		c->addGoal(this);
	}
};

void rowSetup(const int n, vector<vector<Criterion *>> criterion, vector<vector<Goal *>> goal) {
	criterion.resize(8 * n + 5);
	goal.resize(8 * n + 5);
	int patternedRow = (2 * n) + 2;

	// number of goals before pattern begins at Row (2 * n) + 2
	//double endGoals = ((3 * n * n) / (double)2) + ((9 * n) / (double)2) + 3;
	//int endCriterions = (n * n) + (3 * n) + 2;

	int goalNo = 0;
	int criterionNo = 0;
	int k = 1; // horizontal goal counter
	for (int i = 0; i < patternedRow; ++i) {	// first set of special rows
		if (i % 2 == 0) {
			for (int j = 0; j < k; ++j) {
				goal[i].emplace_back(new Goal(goalNo));
				++goalNo;
			}
			for (int j = 0; j < (2 * k); ++j) {
				criterion[i].emplace_back(new Criterion(criterionNo));
				++criterionNo;
			}
		}
		else {
			for (int j = 0; j < (2 * k); ++j) {
				goal[i].emplace_back(new Goal(goalNo));
				++goalNo;
			}
			++k;
		}
	}				
	
	int secondPatternedRow = (6 * n) + 3;
	int temp = n; // number of goal in patternedRow
	for (int i = patternedRow; i < secondPatternedRow; ++i) {
		if (i % 2 == 0) {
			for (int j = 0; j < temp; ++j) {
				goal[i].emplace_back(new Goal(goalNo));
				++goalNo;
			}
			if (temp == n) { ++temp; }
			else { --temp; }
			for (int j = 0; j < ((2 * n) + 2); ++j) {
				criterion[i].emplace_back(new Criterion(criterionNo));
				++criterionNo;
			}
		}
		else {
			for (int j = 0; j < ((2 * n) + 2); ++j) {
				goal[i].emplace_back(new Goal(goalNo));
				++goalNo;
			}
		}
	}

	--k; // horizontal goal counter
	for (int i = secondPatternedRow; i < (8 * n) + 5; ++i) {
		if (i % 2 != 0) {
			for (int j = 0; j < (2 * k); ++j) {
				goal[i].emplace_back(new Goal(goalNo));
				++goalNo;
			}
		}
		else {
			for (int j = 0; j < k; ++j) {
				goal[i].emplace_back(new Goal(goalNo));
				++goalNo;
			}
			for (int j = 0; j < (2 * k); ++j) {
				criterion[i].emplace_back(new Criterion(criterionNo));
				++criterionNo;
			}
			--k;
		}
	}

	for (int i = 0; i < (8 * n) + 5; ++i) {
		cout << "Goals at " << i << ": ";
		int size = goal[i].size();
		for (auto j = 0; j < size; ++j) {
			cout << goal[i][j]->getCoordinate() << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < (8 * n) + 5; ++i) {
		cout << "Criterions at " << i << ": ";
		int size = criterion[i].size();
		for (auto j = 0; j < size; ++j) {
			cout << criterion[i][j]->getCoordinate() << " ";
		}
		cout << endl;
	}
}

void update(const int n, vector<vector<Criterion *>> criterion, vector<vector<Goal *>> goal) {
	//int size = goal.size();
	//for (int j = 0; j < size; ++j) {
	int patternedRow = (2 * n) + 2;

	cout << "It's in update" << endl;

	int goalCounter = 1;
	//int cCounter = 0;
	for (int i = 0; i < patternedRow; ++i) {	
		if (i % 2 == 0) {
			int c = 0;
			for (int g = 0; g < goalCounter; ++g) { // traversing through the goals in row i
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
				//++goalCounter;
			}
			++goalCounter;
		}
		else {}
	}	
}

int main() {
	cout << "Enter the the desired board layer:" << endl;
	int n;
	vector<vector<Criterion *>> criterion;
	vector<vector<Goal *>> goal;
	cin >> n;
	rowSetup(n, criterion, goal);
	update(n, criterion, goal);
	return 1;
}
