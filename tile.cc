#include "tile.h"
#include "criterion.h"
#include <iostream>
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

// 3.5.5
bool Tile::sendResources() {
 bool gained = false;
  if (geeseHere) { return false; } // 2.3
  if (resource == Resource::Netflix) { return false; } // 2.2 (No resources sent)
  for (int i = 0; i < 6; ++i) {
    if (criterion[i]->getStudent()) { // to check if criterion is occupied
     // Student <colour> gained:
      cout << "Student " << criterion[i]->getStudent()->getPlayer() << " gained:" << endl;
      criterion[i]->sendResources(resource);
      gained = true;
    }
  }
  return gained;
}

void Tile::addCriterion(Criterion *c) {
	criterion.emplace_back(c);
}
