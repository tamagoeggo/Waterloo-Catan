#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class TextDisplay: public Observer {
	vector<char> criteriaChar;
	vector<char> goalsChar;
	public:	
	void notify(Criterion &) override;
	void notify(Goal &) override;
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif
