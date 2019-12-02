#include "fair.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

// 2.8
// ctor for a randomly generated fair dice
Fair::Fair() {
  // std::srand(std::time(NULL));
  dice1 = 0;
  dice2 = 0;
}

// roll dice
int Fair::roll() {
	cout << "CHECKPOINT 1" << endl; // DEBUG
  dice1 = rand() % 6 + 1;
  cout << "CHECKPOINT 2" << endl; // DEBUG
  dice2 = rand() % 6 + 1;
  cout << dice2 << endl; // DEBUG
	cout << "CHECKPOINT 3" << endl; // DEBUG
	return dice1 + dice2;
  std::cout << "Dice rolled: " << dice1 + dice2 << std::endl;
}
