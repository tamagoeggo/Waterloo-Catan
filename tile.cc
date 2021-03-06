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
    if(this->criterion[i]->getStudent() == nullptr){
      continue;
    }
    else if(this->criterion[i]->getStudent()->getPlayer() == Player::Blue
    && player != Player::Blue
    && this->criterion[i]->getStudent()->numResources() > 0){
      blueThere = "Blue";
    }
    else if(this->criterion[i]->getStudent()->getPlayer() == Player::Red
    && player != Player::Red
    && criterion[i]->getStudent()->numResources() > 0){
      redThere = "Red";
    }
    else if(this->criterion[i]->getStudent()->getPlayer() == Player::Orange
    && player != Player::Orange
    && this->criterion[i]->getStudent()->numResources() > 0){
      orangeThere = "Orange";
    }
    else if(this->criterion[i]->getStudent()->getPlayer() == Player::Yellow
    && player != Player::Yellow
    && this->criterion[i]->getStudent()->numResources() > 0){
      yellowThere = "Yellow";
    }
  }

  vector<string> printOrder;
  if(blueThere != ""){
    printOrder.emplace_back(blueThere);
  }
  if(redThere != ""){
    printOrder.emplace_back(redThere);
  }
  if(orangeThere != ""){
    printOrder.emplace_back(orangeThere);
  }
  if(yellowThere != ""){
    printOrder.emplace_back(yellowThere);
  }

  int sizeofvec = printOrder.size() - 1;
//  cout << sizeofvec << endl; ///////////////DEBUG//////////////////
  for(int j = 0; j < sizeofvec; j++){
  //  cout << "CHECKPOINT 3"<< endl;
    output += printOrder[j];
    output += ",";
  }
//  cout << "CHECKPOINT 4"<< endl;
  if (!printOrder.empty()){
    output += printOrder.back();
  }
  return output;
}
