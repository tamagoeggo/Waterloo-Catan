#include "tile.h"

// tile ctor
Tile::Tile(int value, Resource res):value{value}, resource{res}{
  // initialize criterion depending on value
}

// changes bool value to true or false if geese is on tile
void Tile::toggleGeese(){
  if(!geeseHere){
    geeseHere = true;
  }
  else if(geeseHere){
    geeseHere = false;
  }
}
