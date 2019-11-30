#include <iostream>
#include <vector>
#include <array>
#include "g.h"
#include "crit.h"

using namespace std;

void rowSetup(const int n, vector<vector<Criterion *>> &criterion, vector<vector<Goal *>> &goal) {
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

	// for (int i = 0; i < (8 * n) + 5; ++i) {
	// 	cout << "Goals at " << i << ": ";
	// 	int size = goal[i].size();
	// 	for (auto j = 0; j < size; ++j) {
	// 		cout << goal[i][j]->getCoordinate() << " ";
	// 	}
	// 	cout << endl;
	// }

	// for (int i = 0; i < (8 * n) + 5; ++i) {
	// 	cout << "Criterions at " << i << ": ";
	// 	int size = criterion[i].size();
	// 	for (auto j = 0; j < size; ++j) {
	// 		cout << criterion[i][j]->getCoordinate() << " ";
	// 	}
	// 	cout << endl;
	// }
}

void update(const int n, vector<vector<Criterion *>> &criterion, vector<vector<Goal *>> &goal) {
	int patternedRow = (2 * n) + 2;

	int goalCounter = 1;
	for (int i = 0; i < patternedRow; ++i) {	
		if (i % 2 == 0) {
			int c = 0;
			for (int g = 0; g < goalCounter; ++g) { // traversing through the goals in row i
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
			}
			++goalCounter;
		}
		else {
			//adding the first criterion to goal
			int size = goal[i].size();
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g]);
				//cout << criterion[i + 1][g + 1]->getCoordinate() << endl;
				if (i == patternedRow - 1) {
					goal[i][g]->addNeighbor(criterion[i + 1][g]);
				}
				else { 
					goal[i][g]->addNeighbor(criterion[i + 1][g + 1]);
				}
			}
		}
	}

	// entering patternedRow
	int secondPatternedRow = (6 * n) + 3;
	for (int i = patternedRow; i <= secondPatternedRow; ++i) {
		int size = goal[i].size();
		if (i % 2 == 0) {
			if (size == n) {
				int cCounter = 1;
				for (int g = 0; g < size; ++g) {
					goal[i][g]->addNeighbor(criterion[i][cCounter]);
					++cCounter;
					goal[i][g]->addNeighbor(criterion[i][cCounter]);
					++cCounter;
				}
			}
			else {
				int cCounter = 0;
				for (int g = 0; g < size; ++g) {
					goal[i][g]->addNeighbor(criterion[i][cCounter]);
					++cCounter;
					goal[i][g]->addNeighbor(criterion[i][cCounter]);
					++cCounter;
				}
			}
		}
		else {
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g]);
				goal[i][g]->addNeighbor(criterion[i + 1][g]);
			}
		}
	}
	
	int gCounter = n + 1;
	for (int i = secondPatternedRow + 1; i < (8 * n) + 5; ++i) {
		int size = goal[i].size();
		if (i % 2 == 0) {
			int c = 0;
			for (int g = 0; g < gCounter; ++g) {
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
				goal[i][g]->addNeighbor(criterion[i][c]);
				++c;
			}
			--gCounter;
		}
		else {
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g + 1]);
				goal[i][g]->addNeighbor(criterion[i + 1][g]);
			}
		}
	}

	// for (int i = 0; i < (8 * n) + 5; ++i) { // for printing
	// 	cout << "At Row " << i << ": " << endl;
	// 	int size = goal[i].size();
	// 	for (int j = 0; j < size; ++j) {
	// 		cout << "Criterion " << goal[i][j]->getCoordinate() << " has goal: ";
	// 		criterion[i][j]->getGoals();
	// 		cout << endl;
	// 	}
	// 	cout << endl;
	// }

	// for (int i = 0; i < (8 * n) + 5; ++i) { // for printing
	// 	cout << "At Row " << i << ": " << endl;
	// 	int size = goal[i].size();
	// 	for (int j = 0; j < size; ++j) {
	// 		cout << "Goal " << goal[i][j]->getCoordinate() << " has criterion: ";
	// 		goal[i][j]->getNeighbors();
	// 		cout << endl;
	// 	}
	// 	cout << endl;
	// }
}

int main() {
	cout << "Enter the the desired board layer:" << endl;
	int n;
	vector<vector<Criterion *>> criterion;
	vector<vector<Goal *>> goal;
	cin >> n;
	rowSetup(n, criterion, goal);
	update(n, criterion, goal);
	criterion[0][0]->upgradeCompletion();
	for (int i = 0; i < (8 * n) + 5; ++i) { // for printing
		cout << "At Row " << i << ": " << endl;
		int size = goal[i].size();
		for (int j = 0; j < size; ++j) {
			cout << "Goal " << goal[i][j]->getCoordinate() << " has criterion: ";
			goal[i][j]->printCompletion();
			cout << endl;
		}
		cout << endl;
	}
	return 1;
}
