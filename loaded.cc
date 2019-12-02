#include "loaded.h"
#include <iostream>

Loaded::Loaded(int num) {
  value = num;
}

int Loaded::roll() {
  return value;
  std::cout << "Dice rolled: " << value << std::endl;
}
