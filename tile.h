#ifndef _TILE_H_
#define _TILE_H_

#include <vector>
#include "resource.h"
#include "player.h"

class Criterion;

class Tile {
	bool geeseHere = false; // true or false
	int value; // value of tile needed to be rolled
	Resource resource; // resource on tile
	std::vector<Criterion *> criterion; // to check which tiles are occupied
	public:
	//ctor
	Tile(int value, Resource res);
	Resource getResource();
	int getValue();
	void toggleGeese(); // changes bool value to true or false if geese is on tile
	bool sendResources(); // updates student’s resources if criteria of the tile is occupied
	void addCriterion(Criterion *c);
	std::string playersToStealFrom(Player); // returns a string of all the players on tile except for the parameter
};

#endif
