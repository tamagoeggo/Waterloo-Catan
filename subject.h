#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "state.h"

class Subject {
	virtual State getState() = 0;
	public:
	virtual ~Subject() = 0; //dtor
};


#endif
