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

// returns a string of all the players on tile except for the parameter
string Tile::playersToStealFrom(Player player){
  // order is always Blue, Red, Orange, Yellow
  string output = "";
  string blueThere = "";
  string redThere = "";
  string orangeThere = "";
  string yellowThere = "";
  for(int i = 0; i < 6; i++){
    if(criterion[i]->getStudent()->getPlayer() == Player::Blue
    && player != Player::Blue
    && criterion[i]->getStudent()->numResources() > 0){
      blueThere = "Blue";
    }
    else if(criterion[i]->getStudent()->getPlayer() == Player::Red
    && player != Player::Red
    && criterion[i]->getStudent()->numResources() > 0){
      redThere = "Red";
    }
    else if(criterion[i]->getStudent()->getPlayer() == Player::Orange
    && player != Player::Orange
    && criterion[i]->getStudent()->numResources() > 0){
      orangeThere = "Orange";
    }
    else if(criterion[i]->getStudent()->getPlayer() == Player::Yellow
    && player != Player::Yellow
    && criterion[i]->getStudent()->numResources() > 0){
      yellowThere = "Yellow";
    }
  }
  vector<string> printOrder;
  printOrder.emplace_back(blueThere);
  printOrder.emplace_back(redThere);
  printOrder.emplace_back(orangeThere);
  printOrder.emplace_back(yellowThere);

  for(int i = 0; i < 4; i++){
    if(printOrder[i] == ""){
      printOrder.erase(printOrder.begin() + i);
    }
  }

  // blue, orange, yellow
  for(int j = 0; j < printOrder.size() - 1; j++){
    output += printOrder[j];
    output += ",";
  }
  if (!printOrder.empty()){
    output += printOrder.back();
  }
  return output;
}
