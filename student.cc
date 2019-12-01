#include "student.h"
#include "type.h"
#include "state.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include <algorithm>    // std::random_shuffle
#include <ctime>
#include <cstdlib>      // std::rand, std::srand
#include "criterion.h"
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

// return the total number of resources as an ini
int Student::numResources(){
  return resources.size();
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
  output += num;
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
  int points = 0;
  for(const auto &completed: criteria){
    if(completed->getState().type == Type::Assignment){
      points += 1;
    }
    else if(completed->getState().type == Type::Midterm){
      points += 2;
    }
    else if(completed->getState().type == Type::Exam){
      points += 3;
    }
  }
  return points;
}

// student steals resources from another student
// only called if there is a student to steal from
// checking happens elsewhere
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

// checks if student will lose resources from a geese roll
//  Any student with 10 or more resources will lose half of their resources (rounded down)
// 3.6
void Student::loseResources(){
  if(numResources() >= 10){
    int numLost = numResources() / 2;
    vector<Resource> keys;
    int numCaffeines = 0;
    int numLabs = 0;
    int numLectures = 0;
    int numStudies = 0;
    int numTutorials = 0;
    cout << "Student " << player << " loses " << numLost << " resources to the geese. They lose:" << endl;
     //srand(time(NULL)); // seed

    for(const auto &res : resources){
      keys.emplace_back(res.first);
    }

    for(int i = 0; i < numLost; i++){
      random_shuffle(keys.begin(), keys.end());
      while(this->resources.[keys.front()] == 0){
        random_shuffle(keys.begin(), keys.end());
      }
      if(keys.front() == Resource::Caffeine){
        numCaffeines += 1;
        this->resources.[keys.front()] -= 1;
      }
      else if(keys.front() == Resource::Lab){
        numLabs += 1;
        this->resources.[keys.front()] -= 1;
      }
      else if(keys.front() == Resource::Lecture){
        numLectures += 1;
        this->resources.[keys.front()] -= 1;
      }
      else if(keys.front() == Resource::Study){
        numStudies += 1;
        this->resources.[keys.front()] -= 1;
      }
      else if(keys.front() == Resource::Tutorial){
        numTutorials += 1;
        this->resources.[keys.front()] -= 1;
      }
    }

    // <numResource> <resourceName>
    if(numCaffeines != 0){
      cout << numCaffeines << " " << "Caffeine" << endl;
    }
    if(numLabs != 0){
      cout << numLabs << " " << "Lab" << endl;
    }
    if(numLectures != 0){
      cout << numLectures << " " << "Lecture" << endl;
    }
    if(numStudies != 0){
      cout << numStudies << " " << "Study" << endl;
    }
    if(numTutorials != 0){
      cout << numTutorials << " " << "Tutorial" << endl;
    }
  }
}

bool Student::resourcesCheck(Type type) {
  if (type == Type::Assignment) {
    if (resources[Resource::Caffeine] < 1) return false;
    if (resources[Resource::Lab] < 1) return false;
    if (resources[Resource::Lecture] < 1) return false;
    if (resources[Resource::Tutorial] < 1) return false;
    return true;
  }
  else if (type == Type::Midterm) {
    if (resources[Resource::Lecture] < 2) return false;
    if (resources[Resource::Study] < 3) return false;
    return true;
  }
  else if (type == Type::Exam) {
    if (resources[Resource::Caffeine] < 3) return false;
    if (resources[Resource::Lab] < 2) return false;
    if (resources[Resource::Lecture] < 2) return false;
    if (resources[Resource::Tutorial] < 1) return false;
    if (resources[Resource::Study] < 2) return false;
    return true;
  }
  else if (type == Type::Achievement) {
    if (resources[Resource::Tutorial] < 1) return false;
    if (resources[Resource::Study] < 1) return false;
    return true;
  }
  else {
    throw "Invalid type.";
  }
}

void Student::resourcesSpent(Type type) {
  if (type == Type::Assignment) {
    resources[Resource::Caffeine] -= 1;
    resources[Resource::Lab] -= 1;
    resources[Resource::Lecture] -= 1;
    resources[Resource::Tutorial] -= 1;
  }
  else if (type == Type::Midterm) {
    resources[Resource::Lecture] -= 2;
    resources[Resource::Study] -= 3;
  }
  else if (type == Type::Exam) {
    resources[Resource::Caffeine] -= 3;
    resources[Resource::Lab] -= 2;
    resources[Resource::Lecture] -= 2;
    resources[Resource::Tutorial] -= 1;
    resources[Resource::Study] -= 2;
  }
  else if (type == Type::Achievement) {
    resources[Resource::Tutorial] -= 1;
    resources[Resource::Study] -= 1;
  }
  else {
    throw "Invalid type.";
  }
}
