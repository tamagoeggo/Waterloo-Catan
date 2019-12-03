#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(std::vector<int> *values, std::vector<Resource> *resources) {
	//vector<string> newValuesString;
	//vector<string> newResourcesString;
	int netflixAt = -1;
	for(int i = 0; i <= 18; ++i) {
		string toEmplace;
		if ((*resources)[i] == Resource::Caffeine) {
			toEmplace = "    CAFFEINE    ";
		} else if ((*resources)[i] == Resource::Lab) {
			toEmplace = "       LAB      ";
		} else if ((*resources)[i] == Resource::Lecture) {
			toEmplace = "     LECTURE    ";
		} else if ((*resources)[i] == Resource::Study) {
			toEmplace = "      STUDY     ";
		} else if ((*resources)[i] == Resource::Tutorial) {
			toEmplace = "    TUTORIAL    ";
		} else if ((*resources)[i] == Resource::Netflix) {
			toEmplace = "     NETFLIX    ";
			netflixAt = i;
		} else { // (resource == Resource::None)
			toEmplace = "                ";
		}
		resourcesString[i] = toEmplace;
	}
	int i = 0;
	int j = 0;
	while (j <= 18) {
		//cout << value << endl;
		//int valuePosn = 0;
		string toEmplace;
		if (i == netflixAt) {
			toEmplace = "                 ";
			netflixAt = -1;
		} else if ((*values)[i] < 10) {
			toEmplace = "        " + to_string((*values)[i]) + "       ";
		} else {
			toEmplace = "       " + to_string((*values)[i]) + "       ";
		}
		valuesString[j] = toEmplace;
		++j;
		if (netflixAt != -1) {
			++i;
		} else {
			netflixAt = -2;
		}
		//++j;
		//++valuePosn;
	}
	//this->valuesString = newValuesString;	// not sure if this actually uses the copy constructor
	//this->resourcesString = newResourcesString;
}

void TextDisplay::notify(Criterion *criterion) {
	State state = criterion->getState();
	string toReplace = "";
	if (state.player == Player::Blue) {
		toReplace += "\u001b[38;5;33;1mB";
	} else if (state.player == Player::Red) {
		toReplace += "\u001b[38;5;196;1mR";
	} else if (state.player == Player::Orange) {
		toReplace += "\u001b[38;5;208;1mO";
	} else if (state.player == Player::Yellow) {
		toReplace += "\u001b[38;5;11;1mY";
	}
	if (state.type == Type::Assignment) {
		toReplace += "A\u001B[0m";
	} else if (state.type == Type::Midterm) {
		toReplace += "M\u001B[0m";
	} else if (state.type == Type::Exam) {
		toReplace += "E\u001B[0m";
	}
	this->criteriaString[state.coordinate] = toReplace;
}

void TextDisplay::notify(Goal *goal) {
	State state = goal->getState();
	string toReplace = "";
	if (state.player == Player::Blue) {
		toReplace += "\u001b[38;5;33;1mB";
	} else if (state.player == Player::Red) {
		toReplace += "\u001b[38;5;196;1mR";
	} else if (state.player == Player::Orange) {
		toReplace += "\u001b[38;5;208;1mO";
	} else if (state.player == Player::Yellow) {
		toReplace += "\u001b[38;5;11;1mY";
	}
	if (state.type == Type::Achievement) {
		toReplace += "A\u001B[0m";
	}
	this->goalsString[state.coordinate] = toReplace;
}

void TextDisplay::notify(int geeseAt) {
	this->geeseAt = geeseAt;
}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	// when size is two, we increment twice, when size is one, we increment once
	//int tileNumber = 0;

	int oddToIncrement = 2;
	int evenToIncrement = 2;
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
	int c = 0; // criterion
	int g = 0; // goal
	int v = 0; // value
	int t = 0; // tilenumber
	int r = 0; // resource
	while (c < criteriaLength && g < goalLength) {
		if (lineNum == 1 || lineNum == 2 || lineNum == 40 || lineNum == 41) {
			out << "                                   ";
		} else if (lineNum == 3 || lineNum == 4 ||
			lineNum == 38 || lineNum == 39) {
			out << "                                 ";
		} else if (lineNum == 5 || lineNum == 6 ||
			lineNum == 36 || lineNum == 37) {
			out << "                    ";
		} else if (lineNum == 7 || lineNum == 8 ||
			lineNum == 34 || lineNum == 35) {
			out << "                  ";
		} else if (lineNum == 9 || lineNum == 10 || lineNum == 16 ||
			lineNum == 17 || lineNum == 18 || lineNum == 24 || lineNum == 25 ||
			lineNum == 26 || lineNum == 32 || lineNum == 33) {
			out << "     ";
		} else if (lineNum == 11 || lineNum == 12 || lineNum == 14 ||
			lineNum == 15 || lineNum == 19 || lineNum == 20 || lineNum == 22 ||
			lineNum == 23 || lineNum == 27 || lineNum == 28 || lineNum == 30 ||
			lineNum == 31) {
			out << "   ";
		}
		// things that look like / \ should have the resource types, things that look like \ / should have geese
		if (lineNum == 2) {
			out << "/            \\" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 4) {
			out << "/" << td.resourcesString[r] << "\\" << endl;
			++r;
			++lineNum;
			continue;
		} else if (lineNum == 6) {
			if (td.geeseAt == 0) {
				out << "/            \\      GEESE     /            \\" << endl;
			} else {
				out << "/            \\                /            \\" << endl;
			}
			++lineNum;
			continue;
		} else if (lineNum == 8) {
			out << "/" << td.resourcesString[r] << "\\";
			++r;
			out << "            ";
			out << "/" << td.resourcesString[r] << "\\" << endl;
			++r;
			++lineNum;
			continue;
		} else if (lineNum == 10 || lineNum == 18 || lineNum == 26) {
			if (lineNum == 10 && td.geeseAt == 1) {
				out << "/            \\      GEESE     /            \\                /            \\" << endl;
			} else if (lineNum == 10 && td.geeseAt == 2) {
				out << "/            \\                /            \\      GEESE     /            \\" << endl;
			} else if (lineNum == 18 && td.geeseAt == 6) {
				out << "/            \\      GEESE     /            \\                /            \\" << endl;
			} else if (lineNum == 18 && td.geeseAt == 7) {
				out << "/            \\                /            \\      GEESE     /            \\" << endl;
			} else if (lineNum == 26 && td.geeseAt == 11) {
				out << "/            \\      GEESE     /            \\                /            \\" << endl;
			} else if (lineNum == 26 && td.geeseAt == 12) {
				out << "/            \\                /            \\      GEESE     /            \\" << endl;
			} else {
				out << "/            \\                /            \\                /            \\" << endl;
			}
			++lineNum;
			continue;
		} else if (lineNum == 12 || lineNum == 20 || lineNum == 28) {
			out << "/" << td.resourcesString[r] << "\\";
			++r;
			out << "            ";
			out << "/" << td.resourcesString[r] << "\\";
			++r;
			out << "            ";
			out << "/" << td.resourcesString[r] << "\\" << endl;
			++r;
			++lineNum;
			continue;
		} else if (lineNum == 14 || lineNum == 22 || lineNum == 30) {
			if ((lineNum == 14 && td.geeseAt == 3) ||
			 (lineNum == 22 && td.geeseAt == 8) ||
			 (lineNum == 30 && td.geeseAt == 13)) {
				out << "\\      GEESE     /            \\                /            \\                /" << endl;
			} else if ((lineNum == 14 && td.geeseAt == 4) ||
				(lineNum == 22 && td.geeseAt == 9) ||
				(lineNum == 30 && td.geeseAt == 14)) {
				out << "\\                /            \\      GEESE     /            \\                /" << endl;
			} else if ((lineNum == 14 && td.geeseAt == 5) ||
				(lineNum == 22 && td.geeseAt == 10) ||
				(lineNum == 30 && td.geeseAt == 15)) {
				out << "\\                /            \\                /            \\      GEESE     /" << endl;
			} else {
				out << "\\                /            \\                /            \\                /" << endl;
			}
			++lineNum;
			continue;
		} else if (lineNum == 16 || lineNum == 24 || lineNum == 32) {
			out << "\\            ";
			out << "/" << td.resourcesString[r] << "\\";
			++r;
			out << "            ";
			out << "/" << td.resourcesString[r] << "\\";
			++r;
			out << "            /" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 34) {
			if (td.geeseAt == 16) {
				out << "\\      GEESE     /            \\                /" << endl;
			} else if (td.geeseAt == 17) {
				out << "\\                /            \\      GEESE     /" << endl;
			} else {
				out << "\\                /            \\                /" << endl;
			}
			++lineNum;
			continue;
		} else if (lineNum == 36) {
			out << "\\            /";
			out << td.resourcesString[r];
			++r;
			out << "\\            /" << endl;
			++lineNum;
			continue;
		} else if (lineNum == 38) {
			if (td.geeseAt == 18) {
				out << "\\      GEESE     /" << endl;
			} else {
				out << "\\                /" << endl;
			}
			++lineNum;
			continue;
		} else if (lineNum == 40) {
			out << "\\            /" << endl;
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
					if (numGoal > 0) {
						out << td.valuesString[v]; // value of board
						++v;
					}
					out << "|" << td.criteriaString[c] << "|";
					++c;
					out << "--" << td.goalsString[g] << "--";
					++numGoal;
					++g;
					out << "|" << td.criteriaString[c] << "|";
					++c;
					//if (numGoal > 0) {
					//	out << td.valuesString[v]; // value of board
					//	++v;
					//}
				}
			} else {
				out << "|" << td.criteriaString[c] << "|";
				++c;
				out << td.valuesString[v]; // value of board
				++v;
				while (numGoal < oddGoalPerLine) {
					if (numGoal > 0) {
						out << td.valuesString[v]; // value of board
						++v;
					}
					out << "|" << td.criteriaString[c] << "|";
					++c;
					out << "--" << td.goalsString[g] << "--";
					++numGoal;
					++g;
					out << "|" << td.criteriaString[c] << "|";
					++c;
				}
				out << td.valuesString[v]; // value of board
				++v;
				out << "|" << td.criteriaString[c] << "|";
				++c;
			}
			if (oddToIncrement > 0) {
				--oddToIncrement;
				oddCriterionPerLine += 2;
				oddGoalPerLine += 1;
			} else if (oddToIncrement == 0) {
				--oddToIncrement;
				oddToRepeat = 6; // not sure if this works for 3 layers
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
					if (lineNum == 3) {
						out << td.tileNumberString[t]; // tile number kinda goes here
						++t;
					} else if (lineNum == 7) {
						if (numGoal == 1 || numGoal == 3) {
							out << td.tileNumberString[t]; // tile number kinda goes here
							++t;
						} else {
							out << "             ";
						}

					} else if (lineNum == 11 || lineNum == 19 || lineNum == 27) {
						if (numGoal == 1 || numGoal == 3 || numGoal == 5) {
							out << td.tileNumberString[t]; // tile number kinda goes here
							++t;
						} else {
							out << "             ";
						}
					} else if (lineNum == 15 || lineNum == 23 || lineNum == 31) {
						if (numGoal == 2 || numGoal == 4) {
							out << td.tileNumberString[t]; // tile number kinda goes here
							++t;
						} else {
							out << "             ";
						}
					} else if (lineNum == 35) {
						if (numGoal == 2) {
							out << td.tileNumberString[t]; // tile number kinda goes here
							++t;
						} else {
							out << "             ";
						}
					} else {
						out << "             ";
					}
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
				evenToRepeat = 4; // not sure if this works for 3 layers
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
