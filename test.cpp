#include <memory>
#include <iostream>
#include <string>
using namespace std;

class Student {
	string myStudent;
public:
	Student(string myStudent) : myStudent{myStudent} {}
	string getStudent() {
		return myStudent;
	}
};

class Criterion { // Vertex
	unique_ptr<Student> occupiedBy;
public:
	void updateOccupant(unique_ptr<Student> newOccupant); // updates occupiedBy
	string getStudent();
};

void Criterion::updateOccupant(unique_ptr<Student> newOccupant) {
	occupiedBy = move(newOccupant);
}

string Criterion::getStudent() {
	return occupiedBy->getStudent();
}

int main () {
	unique_ptr<Student> studentOne = make_unique<Student>(Student("one"));
	// Auto p = make_unique<MyClass>();
	Criterion *c = new Criterion();
	c->updateOccupant(move(studentOne));
	string toPrint = c->getStudent();
	cout << toPrint;
	delete c;
}
