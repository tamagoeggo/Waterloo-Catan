#include "student.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include <vector>
using namespace std;

// ctor
Student::Student(Player player) : player{player} {}

// gets player color
// can be either {Blue, Red, Orange, Yellow, None}
Player Student::getPlayer() {
  return player;
}

// updates the number and type of resource a student has
void Student::updateResources(Resource resource, int amount) {
  resources[resource] += amount;
}

// updates the vector of criterion a student has completed
void Student::updateCriterion(Criterion *crit) {
  criteria.emplace_back(crit);
}

// updates the vector of goals a student has completed
void Student::updateGoal(Goal *goal) {
  goals.emplace_back(goal);
}

// A student’s data is printed out as follows:
// <numCaffeines> <numLabs> <numLectures> <numStudies> <numTutorials> g <goals> c <criteria>
// returns number of each resource in the order spsecified as s string separated by spaces
string Student::returnResources() {
  string output = "";
  string num = "0";

  if(resources.count(Resource::Caffeine)) {
    num = std::to_string(resources[Resource::Caffeine]);
  }
  output += num + " ";
  num = "0";
  if(resources.count(Resource::Lab)) {
    num = to_string(resources[Resource::Lab]);
  }
  output += num + " ";
  num = "0";
  if(resources.count(Resource::Lecture)) {
    num = to_string(resources[Resource::Lecture]);
  }
  output += num + " ";
  num = "0";
  if(resources.count(Resource::Study)) {
    num = to_string(resources[Resource::Study]);
  }
  output += num + " ";
  num = "0";
  if(resources.count(Resource::Tutorial)) {
    num = to_string(resources[Resource::Tutorial]);
  }
  output += "and " + num + " ";
  num = "0";

  return output;
}

// A student’s data is printed out as follows:
// <numCaffeines> <numLabs> <numLectures> <numStudies> <numTutorials> g <goals> c <criteria>
// returns the number of gaols the student has
string Student::returnGoals(){
  string output = "";
  string num = to_string(goals.size());
  output += num;
  return output;
}


// A student’s data is printed out as follows:
// <numCaffeines> <numLabs> <numLectures> <numStudies> <numTutorials> g <goals> c <criteria>
// returns the number of criteria a student has
string Student::returnCriteria(){
  string output = "";
  string num = to_string(criteria.size());
  output += num;
  return output;
}


// prints the resource status of the student
// reference assignment section 2.7
string Student::printResources(){
  string output = "";
  string num = "0";

  if(resources.count(Resource::Caffeine)){
    num = to_string(resources[Resource::Caffeine]);
  }
  output += num + " caffeines, ";
  num = "0";
  if(resources.count(Resource::Lab)){
    num = to_string(resources[Resource::Lab]);
  }
  output += num + " labs, ";
  num = "0";
  if(resources.count(Resource::Lecture)){
    num = to_string(resources[Resource::Lecture]);
  }
  output += num + " lectures, ";
  num = "0";
  if(resources.count(Resource::Study)){
    num = to_string(resources[Resource::Study]);
  }
  output += num + " studies, ";
  num = "0";
  if(resources.count(Resource::Tutorial)){
    num = to_string(resources[Resource::Tutorial]);
  }
  output += "and " + num + " tutorials";
  num = "0";

  return output;
// <numCaffeines> caffeines, <numLabs> labs, <numLectures> lectures, <numStudies> studies, and <numTutorials> tutorials
}

// prints the goals of the student
// string Student::printGoals(){
//   string output = "";
//   return output;
// }

// returns the number of criteria a student has completed
string Student::printCriteria(){
  string output = "";
  string num = std::to_string(criteria.size());
  output += num + " course criteria, ";
  return output;
}

void Student::printStatus(){// calls printResources, printGoals, printCriteria
// <colour> has <numCC> course criteria, <numCaffeines> caffeines, <numLabs> labs, <numLectures> lectures, <numStudies> studies, and <numTutorials> tutorials.
  cout << player << " has " << printCriteria() << printResources() << std::endl;
}

// trades the current student's resources and the other student's if the trade goes through / is valid
// active student is current student <colour1> </colour1></colour>(proposing a trade)
void Student::trade(Student stud, Resource resource1, Resource resource2){
//  <colour1> offers <colour2> one <resource1> for one <resource2>. Does <colour2> accept this offer?
  cout << this->player << " offers " << stud.player << " one " << resource1 << " for one " << resource2 << ". Does " << stud.player << " accept this offer?" << endl;
  string answer;
  cin >> answer;
  if(answer == "no") {
    return;
  }
  else if(answer == "yes") {
    // assume all valid moves
    // add exceptions later
    this->resources[resource2] += 1;
    this->resources[resource1] -= 1;
    stud.resources[resource1] += 1;
    stud.resources[resource2] -= 1;
    return;
  }
  else {
    cout << "place catch block here" << endl;
    return;
  }
}

// returns the points, which is the number of completed criterions a student has
int Student::getPoints(){
  return criteria.size();
}

// student steals resources from another student
// only called if there is a student to steal from
void Student::stealResources(Student &student){
  // Student <colour1> steals <resource> from student <colour2>.
  cout << "Student " << player << " steals " << "resource" << " from student " << student.player << endl;
  // probablity of being stolen from
  Resource steal = Resource::None;
  float probablity = 0.00;
  int total = resources.size();
  if(!total){
    total = 1;
  }
  for (auto const& x : student.resources){
      if(x.second / total > probablity){
        probablity = x.second / total;
        steal = x.first;
      }
    }

  if(steal == Resource::None){
    cout << "exception block here for when there is nothing to be stolen" << endl;
    return;
  }
  else{
    //Student Blue steals LECTURE from student Yellow
    cout << "Student " << player << " steals " << steal << " from student " << student.player << endl;
    this->resources[steal] += 1;
    student.resources[steal] -= 1;
    return;
  }
}


void Student::loseResources(){
  return;
}
