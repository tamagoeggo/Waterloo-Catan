#include "loaded.h"

Loaded::Loaded(int num) {
  value = num;
}

int Loaded::roll() {
  return value;
  std::cout << "Dice rolled: " << value << std::endl;
}
