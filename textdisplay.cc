// test hardcoded textdisplay
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TextDisplay/*: public Observer*/ {
	int size = 2;	// we are going to do all of this hardcoding in the constructor call
	int numTiles = 18;
	vector<string> criteriaString = {" 0", " 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10",
		"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
		"21", "22", "23", "24", "25", "26", "27", "28", "29", "30",
		"31", "32", "33", "34", "35", "36", "37", "38", "39", "40",
		"41", "42", "43", "44", "45", "46", "47", "48", "49", "50",
		"51", "52", "53"};
	vector<string> goalsString = {" 0", " 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10",
		"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
		"21", "22", "23", "24", "25", "26", "27", "28", "29", "30",
		"31", "32", "33", "34", "35", "36", "37", "38", "39", "40",
		"41", "42", "43", "44", "45", "46", "47", "48", "49", "50",
		"51", "52", "53", "54", "55", "56", "57", "58", "59", "60",
		"61", "62", "63", "64", "65", "66", "67", "68", "69", "70",
		"71"};
	vector<string> resourcesString = {"CAFFEINE", "LAB", "STUDY", "LAB", 
		"NETFLIX", "STUDY", "LECTURE", "CAFFEINE", "STUDY", "CAFFEINE",
		"CAFFEINE", "LAB", "TUTORIAL", "LAB", "TUTORIAL", "LECTURE",
		"TUTORIAL", "LECTURE", "LECTURE"};
	public:	
	//void notify(Criterion &) override;
	//void notify(Goal &) override;
	friend ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

//vector<string> TextDisplay::criteriaString

//std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	// when size is two, we increment twice, when size is one, we increment once
	int oddToIncrement = td.size;
	int evenToIncrement = td.size;
	int oddToRepeat = 0;
	int evenToRepeat = 0;
	//int evenCriterionPerLine = 0;
	int evenGoalPerLine = 2;
	int oddCriterionPerLine = 2;
	int oddGoalPerLine = 1;
	int criteriaLength = td.criteriaString.size();
	int goalLength = td.goalsString.size();
	bool odd = true;
	bool decremented = true;
	int lineNum = 1;
	int c = 0;
	int g = 0;
	while (c < criteriaLength && g < goalLength) {
		if (lineNum == 1 || lineNum == 41) {
			out << "                                   ";
		} else if (lineNum == 3 || lineNum == 39) {
			out << "                                 ";
		} else if (lineNum == 5 || lineNum == 37) {
			out << "                    ";
		} else if (lineNum == 7 || lineNum == 35) {
			out << "                  ";
		} else if (lineNum == 9 || lineNum == 17 || lineNum == 25 || 
			lineNum == 33) {
			out << "     ";
		} else if (lineNum == 11 || lineNum == 15 || lineNum == 19 || 
			lineNum == 23 || lineNum == 27 || lineNum == 31) {
			out << "   ";
		}
		if (lineNum == 2) {
			out << "                                   /            \\" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 4) {
			out << "                                 /                \\" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 6) {
			out << "                    /            \\                /            \\" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 8) {
			out << "                  /                \\            /                \\" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 10 || lineNum == 18 || lineNum == 26) {
			out << "     /            \\                /            \\                /            \\" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 12 || lineNum == 20 || lineNum == 28) {
			out << "   /                \\            /                \\            /                \\" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 14 || lineNum == 22 || lineNum == 30) {
			out << "   \\                /            \\                /            \\                /" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 16 || lineNum == 24 || lineNum == 32) {
			out << "     \\            /                \\            /                \\            /" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 34) {
			out << "                  \\                /            \\                /" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 36) {
			out << "                    \\            /                \\            /" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 38) {
			out << "                                 \\                /" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 40) {
			out << "                                   \\            /" << endl;
			++lineNum;
			continue;
		}
		int numGoal = 0;
		if (odd) {
			//out << "oddToRepeat is " << oddToRepeat << endl; // DEBUG
			//out << "oddCriterionPerLine is " << oddCriterionPerLine << endl; // DEBUG
			//out << "oddGoalPerLine is " << oddGoalPerLine << endl; // DEBUG
			if (oddCriterionPerLine == 2 * oddGoalPerLine) { // this means that there is a goal between every 2 criterion
				while (numGoal < oddGoalPerLine) {
					out << "|" << td.criteriaString[c] << "|";
					++c;
					out << "--" << td.goalsString[g] << "--";
					++numGoal;
					++g;
					out << "|" << td.criteriaString[c] << "|";
					++c;
					if (numGoal > 0) {
						out << "                ";
					}
				}
			} else {
				out << "|" << td.criteriaString[c] << "|";
				++c;
				out << "                ";
				while (numGoal < oddGoalPerLine) {
					if (numGoal > 0) {
						out << "                ";
					}
					out << "|" << td.criteriaString[c] << "|";
					++c;
					out << "--" << td.goalsString[g] << "--";
					++numGoal;
					++g;
					out << "|" << td.criteriaString[c] << "|";
					++c;
				}
				out << "                ";
				out << "|" << td.criteriaString[c] << "|";
				++c;
			}
			if (oddToIncrement > 0) {
				--oddToIncrement;
				oddCriterionPerLine += 2;
				oddGoalPerLine += 1;
			} else if (oddToIncrement == 0) {
				--oddToIncrement;
				oddToRepeat = (td.size + 1) * 2; // not sure if this works for 3 layers
				--oddGoalPerLine;
			} else if (oddToRepeat > 0) {
				--oddToRepeat;
				if (decremented) {
					++oddGoalPerLine;
					decremented = false;
				} else {
					--oddGoalPerLine;
					decremented = true;
				}
				if (oddToRepeat == 0) {
					oddCriterionPerLine -= 2;
				}
			} else {
				oddCriterionPerLine -= 2;
				oddGoalPerLine -= 1;
			}
			//criterion += c;
			//goal += g;
			odd = false;
		} else {
			//out << "evenToRepeat is " << evenToRepeat << endl; // DEBUG
			//out << "evenGoalPerLine is " << evenGoalPerLine << endl; // DEBUG
			while (numGoal < evenGoalPerLine) {
				if (numGoal > 0) {
					out << "             ";
				}
				out << td.goalsString[g];
				++numGoal;
				++g;
			}
			if (evenToIncrement > 0) {
				--evenToIncrement;
				evenGoalPerLine += 2;
			} else if (evenToIncrement == 0) {
				--evenToIncrement;
				evenToRepeat = td.size * 2; // not sure if this works for 3 layers
				//evenGoalPerLine -= 2;
			} else if (evenToRepeat > 0) {
				--evenToRepeat;
			} else {
				evenGoalPerLine -= 2;
			}
			//goal += g;
			odd = true;
		}
		++lineNum;
		cout << endl;
	}
	return out;
}

int main() {
	TextDisplay *td = new TextDisplay();
	cout << *td;
	delete td;
}


