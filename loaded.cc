#include "loaded.h"
#include <iostream>

Loaded::Loaded(int num) {
  value = num;
}

int Loaded::roll() {
	std::cout << "Dice rolled: " << value << std::endl;
  return value;
}
