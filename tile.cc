#include "tile.h"
#include "criterion.h"
using namespace std;

Tile::Tile(int value, Resource res):value{value}, resource{res}{
  // initialize criterion depending on value
}

Resource Tile::getResource() {
  return resource;
}

int Tile::getValue() {
  return value;
}

// changes bool value to true or false if geese is on tile
void Tile::toggleGeese() {
  if(!geeseHere){
    geeseHere = true;
  }
  else if(geeseHere){
    geeseHere = false;
  }
}

void Tile::sendResources() {
  for (int i = 0; i < 6; ++i) {
    if (criterion[i]->getStudent()) { // to check if criterion is occupied
      criterion[i]->sendResources(resource);
    }
  }
}

void Tile::addCriterion(Criterion *c) {
	criterion.emplace_back(c);
}
