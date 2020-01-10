#ifndef _DICE_H_
#define _DICE_H_
#include <string>

class Dice {
	public:
		// Factory Method
		static Dice *make_dice(std::string choice);
		virtual void setDie(int num) = 0;
		virtual int roll() = 0;
};

#endif
