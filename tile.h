#ifndef _TILE_H_
#define _TILE_H_

class Tile {
	bool geeseHere = false; // true or false
	int value; // value of tile needed to be rolled
	Resource resource; // resource on tile
	vector<Criterion *> criterion; // to check which tiles are occupied
	public:
	//ctor
	Tile(int value, Resource res);
	void getResource();
	void getValue();
	void toggleGeese(); // changes bool value to true or false if geese is on tile
	void sendResources(); // updates student’s resources if criteria of the tile is occupied
};

#endif
