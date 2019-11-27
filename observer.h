#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Observer {
	virtual void notify(Criterion &) = 0;
	virtual void notify(Goal &) = 0;
};


#endif
