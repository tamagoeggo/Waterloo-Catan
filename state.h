#ifndef _STATE_H_
#define _STATE_H_

#include "player.h"
#include "type.h"

struct State {
	Player player; // player color
	Type type; // achievement, assignment, midterm, exam or none
	int coordinate; // coordinate
};


#endif
