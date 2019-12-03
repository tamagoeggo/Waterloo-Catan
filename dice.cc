#include "dice.h"
#include "fair.h"
#include "loaded.h"
#include <string>
using namespace std;

Dice *Dice::make_dice(string choice) {
	if (choice == "fair") {
		return new Fair;
	}
	else {
		return new Loaded;
	}
}
