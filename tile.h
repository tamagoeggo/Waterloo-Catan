#ifndef _TILE_H_
#define _TILE_H_

class Tile {
	bool geeseHere = false; // true or false
	int value; // value of tile needed to be rolled
	Resource resource; // resource on tile
	vector<Criterion *> criterion = [v1, v2, v3, v4, v5, v6]; // check which tiles are occupied
	public:
	void getResource();
	void getValue();
	void toggleGeese(); // changes bool value to true or false if geese is on tile
	void sendResources(); // updates student’s resources if criteria of the tile is occupied
};

#endif
