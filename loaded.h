#ifndef _LOADED_H_
#define _LOADED_H_

#include "dice.h"

class Loaded: public Dice {
	int value;
	public:
	Loaded(); //ctor
	void setDie(int num);
	int roll();
};

#endif
