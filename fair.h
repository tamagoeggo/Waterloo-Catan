#ifndef _FAIR_H_
#define _FAIR_H_

#include "dice.h"

class Fair: public Dice {
	int dice1;
	int dice2;
	public:
	Fair(); //ctor
	void setDie(int num);
	int roll();
};


#endif
