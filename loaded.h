#ifndef _LOADED_H_
#define _LOADED_H_

#include "dice.h"

class Loaded: public Dice {
	int value;
	public:
	Loaded(int); //ctor
	int roll();
};

#endif
