#include "tile.h"

// changes bool value to true or false if geese is on tile
void Tile::toggleGeese(){
  if(!geeseHere){
    geeseHere = true;
  }
  else if(geeseHere){
    geeseHere = false;
  }
}
