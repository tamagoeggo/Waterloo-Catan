#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <iostream>
#include <string>
#include <vector>
#include "resource.h"
#include "criterion.h"
#include "goal.h"
#include "observer.h"
#include "state.h"

class TextDisplay : public Observer {
	int geeseAt = -1;
	std::vector<std::string> criteriaString = {" 0", " 1", " 2", " 3", " 4",
		" 5", " 6", " 7", " 8", " 9", "10",
		"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
		"21", "22", "23", "24", "25", "26", "27", "28", "29", "30",
		"31", "32", "33", "34", "35", "36", "37", "38", "39", "40",
		"41", "42", "43", "44", "45", "46", "47", "48", "49", "50",
		"51", "52", "53"};
	std::vector<std::string> goalsString = {" 0", " 1", " 2", " 3", " 4", 
		" 5", " 6", " 7", " 8", " 9", "10",
		"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
		"21", "22", "23", "24", "25", "26", "27", "28", "29", "30",
		"31", "32", "33", "34", "35", "36", "37", "38", "39", "40",
		"41", "42", "43", "44", "45", "46", "47", "48", "49", "50",
		"51", "52", "53", "54", "55", "56", "57", "58", "59", "60",
		"61", "62", "63", "64", "65", "66", "67", "68", "69", "70",
		"71"};
	std::vector<std::string> resourcesString = {"    CAFFEINE    ", "       LAB      ", 
		"      STUDY     ", "       LAB      ", "     NETFLIX    ",
		"      STUDY     ", "     LECTURE    ", "    CAFFEINE    ",
	  "      STUDY     ", "    CAFFEINE    ", "    CAFFEINE    ", 
	  "       LAB      ", "    TUTORIAL    ", "       LAB      ", 
	  "    TUTORIAL    ", "     LECTURE    ", "    TUTORIAL    ", 
	  "     LECTURE    ", "     LECTURE    "};
	std::vector<std::string> valuesString = {"        3       ", "       10       ",
		"        5       ", "        4       ", "                ",
		"       10       ", "       11       ", "        3       ", 
		"        8       ", "        2       ", "        6       ", 
		"        8       ", "       12       ", "        5       ", 
		"       11       ", "        4       ", "        6       ", 
		"        9       ", "        9       "};
	std::vector<std::string> tileNumberString = {"       0     ", "       1     ",
		"       2     ", "       3     ", "       4     ",
		"       5     ", "       6     ", "       7     ", 
		"       8     ", "       9     ", "      10     ", 
		"      11     ", "      12     ", "      13     ", 
		"      14     ", "      15     ", "      16     ", 
		"      17     ", "      18     "};
	public:
	TextDisplay(std::vector<int> values, std::vector<Resource> resources);
	void notify(Criterion *criterion);
	void notify(Goal *goal);
	void notify(int geeseAt);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
