#include "fair.h"
#include <stdlib.h>

// 2.8
// ctor for a randomly generated fair dice
Fair::Fair(){
  std::srand(std::time(NULL));
  dice1 = 0;
  dice2 = 0;
}

// roll dice
int Fair::roll() {
	dice1 = rand() % 6 + 1;
	dice2 = rand() % 6 + 1;
	return dice1 + dice2;
}
