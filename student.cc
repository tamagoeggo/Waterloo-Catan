#include "student.h"
#include <map>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include <vector>

// gets player color
// can be either {Blue, Red, Orange, Yellow, None}
Player Student::getPlayer(){
  return player;
}

// updates the number and type of resource a student has
void Student::updateResources(Resource resource, int amount){
  resources[resource] += amount;
}

// updates the vector of criterion a student has completed
void Student::updateCriterion(Criterion *crit){
  criteria.emplace_back(crit);
}

// updates the vector of goals a student has completed
void Student::updateGoal(Goal *goal){
  goals.emplace_back(goal);
}

// prints the resource status of the student
// reference assignment section 2.7
std::string Student::printResources(){
  std::string output = "";
  std::string num = "0";

  if(resources.count(Caffeine)){
    num = std::to_string(resources[Caffeine]);
  }
  output += num + " caffeines, ";
  num = "0";
  if(resources.count(Lab)){
    num = std::to_string(resources[Lab]);
  }
  output += num + " labs, ";
  num = "0";
  if(resources.count(Lecture)){
    num = std::to_string(resources[Lecture]);
  }
  output += num + " lectures, ";
  num = "0";
  if(resources.count(Study)){
    num = std::to_string(resources[Study]);
  }
  output += num + " studies, ";
  num = "0";
  if(resources.count(Tutorial)){
    num = std::to_string(resources[Tutorial]);
  }
  output += "and " + num + " tutorials";
  num = "0";

  return output;
// <numCaffeines> caffeines, <numLabs> labs, <numLectures> lectures, <numStudies> studies, and <numTutorials> tutorials
}

// prints the goals of the student
std::string Student::printGoals(){
  std::string output = "";
  return output;
}

// returns the number of criteria a student has completed
std::string Student::printCriteria(){
  std::string output = "";
  std::string num = std::to_string(criteria.size());
  output += num + " course criteria, ";
  return output;
}

void Student::printStatus(){// calls printResources, printGoals, printCriteria
// <colour> has <numCC> course criteria, <numCaffeines> caffeines, <numLabs> labs, <numLectures> lectures, <numStudies> studies, and <numTutorials> tutorials.
  std::cout << player << " has " << printCriteria() << printResources() << std::endl;
}

// trades the current student's resources and the other student's if the trade goes through / is valid
// active student is current student <colour1> </colour1></colour>(proposing a trade)
void Student::trade(Student stud, Resource resource1, Resource resource2){
//  <colour1> offers <colour2> one <resource1> for one <resource2>. Does <colour2> accept this offer?
  std::cout << this->player << " offers " << stud.player << " one " << resource1 << " for one " << resource2 << ". Does " << stud.player << " accept this offer?" << std::endl;
  std::string answer;
  std::cin >> answer;
  if(answer == "no"){
    return;
  }
  else if(answer == "yes"){
    // assume all valid moves
    // add exceptions later
    this->resources[resource2] += 1;
    this->resources[resource1] -= 1;
    stud.resources[resource1] += 1;
    stud.resources[resource2] -= 1;
    return;
  }
  else{
    std::cout << "place catch block here" << std::endl;
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
  std::cout << "Student " << player << " steals " << "resource" << " from student " << student.player << std::endl;
  // probablity of being stolen from
  Resource steal = Resource::None;
  float probablity = 0;
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
    std::cout << "exception block here for when there is nothing to be stolen" << std::endl;
    return;
  }
  else{
    //Student Blue steals LECTURE from student Yellow
    std::cout << "Student " << player << " steals " << steal << " from student " << student.player << std::endl;
    this->resources[steal] += 1;
    student.resources[steal] -= 1;
    return;
  }
}
