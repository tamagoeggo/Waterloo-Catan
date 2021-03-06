#include "board.h"
#include <sstream>
using namespace std;

// ctor with randomized resources and value, init textdisplay
Board::Board(bool enhance, string board, int layer) {

	// num = (rand() % (upper – lower + 1)) + lower
  	// The board will consist of the following values: one 2, one 12, two 3-6, and two 8-11.
	vector<int> values ={2,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11,12};
  	random_shuffle(values.begin(), values.end());
  	//  The board consists of the following resources: 3 TUTORIAL, 3 STUDY, 4 CAFFEINE, 4 LAB, 4 LECTURE, and 1 NETFLIX
	vector<Resource> resourcetype = {
		Resource::Tutorial,Resource::Tutorial,Resource::Tutorial,
		Resource::Study,Resource::Study,Resource::Study,
		Resource::Caffeine,Resource::Caffeine,Resource::Caffeine,Resource::Caffeine,
    		Resource::Lab,Resource::Lab,Resource::Lab,Resource::Lab,
    		Resource::Lecture,Resource::Lecture,Resource::Lecture,Resource::Lecture,
    		Resource::Netflix
	};
	random_shuffle(resourcetype.begin(), resourcetype.end());

	if (board != "default") {
		stringstream lineStream;
		lineStream << board;
		vector<int> values2;
		vector<Resource> resourceType2vec;
		while (lineStream) {
			int type;
			Resource resourceType2;
			int value;
			lineStream >> type;
			lineStream >> value;
			if (type == 0) {
				resourceType2 = Resource::Caffeine;
			} else if (type == 1) {
				resourceType2 = Resource::Lab;
			} else if (type == 2) {
				resourceType2 = Resource::Lecture;
			} else if (type == 3) {
				resourceType2 = Resource::Study;
			} else if (type == 4) {
				resourceType2 = Resource::Tutorial;
			} else {
				resourceType2 = Resource::Netflix;
			}
			tiles.emplace_back(make_unique<Tile>(value, resourceType2));
			values2.emplace_back(value);
			resourceType2vec.emplace_back(resourceType2);
		}
		td = make_unique<TextDisplay>(enhance, &values2, &resourceType2vec);
	} else {
		// init TextDisplay
  		td = make_unique<TextDisplay>(enhance, &values, &resourcetype);

		// init tiles
		unique_ptr<Tile> newtile;
  		for (int i = 0; i < 19; i++) {
			if(resourcetype.front() == Resource::Netflix){
				newtile = make_unique<Tile>(7, resourcetype.front());
			} else {
      				newtile = make_unique<Tile>(values.front(), resourcetype.front());
      				values.erase(values.begin());
			}
			resourcetype.erase(resourcetype.begin());
    			tiles.emplace_back(move(newtile));
		}
	}
	//srand(time(NULL)); // seed
  	vector<vector<unique_ptr<Criterion>>> criterionv;
  	vector<vector<unique_ptr<Goal>>> goalv;
  	rowSetup(layer, criterionv, goalv);
  	update(layer, criterionv, goalv);

  	// init Criterion
  	size_t total_size{ 0 };
  	for (auto const& row: criterionv) {
		total_size += row.size();
  	}
  	criterion.reserve(total_size);

  	for (unsigned int i = 0; i < criterionv.size(); ++i) {
		unsigned int size = criterionv[i].size();
		for (unsigned int j = 0; j < size; ++j) {
			criterion.emplace_back(move(criterionv[i][j]));
		}
	}

	updateCriterionsNeighbor();

  	// init Goals
  	total_size = 0;
  	for (auto const& row: goalv) {
		total_size += row.size();
	}
  	goals.reserve(total_size);

	for (unsigned int i = 0; i < goalv.size(); ++i) {
		unsigned int size = goalv[i].size();
		for (unsigned int j = 0; j < size; ++j) {
			goals.emplace_back(move(goalv[i][j]));
		}
	}

      	// The assignments will be chosen by students in the order Blue, Red, Orange, Yellow, Yellow, Orange, Red, Blue.
  	// 4.1
  	// init students
  	unique_ptr<Student> newstud1 = make_unique<Student>(Player::Blue);
  	students.emplace_back(move(newstud1));
  	unique_ptr<Student> newstud2 = make_unique<Student>(Player::Red);
  	students.emplace_back(move(newstud2));
  	unique_ptr<Student> newstud3 = make_unique<Student>(Player::Orange);
  	students.emplace_back(move(newstud3));
  	unique_ptr<Student> newstud4 = make_unique<Student>(Player::Yellow);
  	students.emplace_back(move(newstud4));

	updateCriterionsInTile(layer);
}

// dtor
/*
Board::~Board(){
	this->tiles.clear();
	this->criterion.clear();
	this->goals.clear();
	this->students.clear();
	this->td = nullptr;
}
*/

void Board::completeCriterion(const int coordinate, const Player player) {
	int iter;
	for (int i = 0; i < 4; ++i) {
		if (students[i]->getPlayer() == player) {
			iter = i;
			break;
		}
	}
	if (criterion[coordinate]->getStudent()) { // check if criterion is occupied
		throw "You cannot build here because this Criterion is already completed.";
	}
	else if (!criterion[coordinate]->areNeighborsUnoccupied()) {
		throw "You cannot build here because an adjacent Criterion is completed.";
	}
	else if (!criterion[coordinate]->goalsOccupancy(player)) {
		throw "You cannot build here because you have not achieved any adjacent Goal.";
	}
	else if (!students[iter]->resourcesCheck(Type::Assignment)) {
		throw "You cannot build here because you do not have the necessary Resources. An assignment costs one Caffeine, one Lab, one Lecture, and one Tutorial";
	}
	else {
		criterion[coordinate]->updateOccupant(students[iter].get());
		students[iter]->resourcesSpent(Type::Assignment); 				// decrease Player's resources
		students[iter]->updateCriterion(criterion[coordinate].get());	// update Player's criterion owned list
		td->notify(criterion[coordinate].get());
		cout << "You have completed Criterion " << coordinate << "." << endl;
	}
}

void Board::firstCriterion(const int coordinate, Player player) {
	int iter;
	for (int i = 0; i < 4; ++i) {
		if (students[i]->getPlayer() == player) {
			iter = i;
			break;
		}
	}
	if (criterion[coordinate]->getStudent()) { // check if criterion is occupied
		throw "You cannot build here because this Criterion is already completed.";
	}
	else if (!criterion[coordinate]->areNeighborsUnoccupied()) {
		throw "You cannot build here because an adjacent Criterion is completed.";
	}
	else {
		criterion[coordinate]->updateOccupant(students[iter].get());
		students[iter]->updateCriterion(criterion[coordinate].get());
		td->notify(criterion[coordinate].get());
	}
}

void Board::upgradeCriterion(const int coordinate, Player player) {
	int iter;
	for (int i = 0; i < 4; ++i) {
		if (students[i]->getPlayer() == player) {
			iter = i;
			break;
		}
	}
	if (criterion[coordinate]->getStudent() == students[iter].get()) {
		State state = criterion[coordinate]->getState();
		if (!students[iter]->resourcesCheck(state.type)) {
			throw "You cannot build here because you do not have the necessary Resources. A midterm costs two Lecture, and three Study. An exam costs three Caffeine, two Lab, two Lecture, one Tutorial and two Study.";
		}
		criterion[coordinate]->upgrade(); 								// update the type of achievement at criterion
		students[iter]->resourcesSpent(state.type);
		td->notify(criterion[coordinate].get());
		cout << "Criterion " << coordinate << " has been improved." << endl;
	}
	else {
		throw "You cannot build here because you do not own this criterion.";
	}
}

void Board::achieveGoal(const int coordinate, Player player) {
	int iter;
	for (int i = 0; i < 4; ++i) {
		if (students[i]->getPlayer() == player) {
			iter = i;
			break;
		}
	}
	if (goals[coordinate]->getStudent()) { // check if criterion is occupied
		throw "You cannot build here because this Goal is already achieved.";
	}
	else if (!goals[coordinate]->canPlayerAchieveGoal(students[iter].get())) {
		throw "You cannot build here because you have not completed any adjacent Goal(s) or Criterion(s).";
	}
	else if (!students[iter]->resourcesCheck(Type::Achievement)) {
		throw "You cannot build here because you do not have the necessary Resources. The cost of an achievement is one Study and one Tutorial resource";
	}
	else {
		goals[coordinate]->updateOccupant(students[iter].get());
		students[iter]->resourcesSpent(Type::Achievement);
		students[iter]->updateGoal(goals[coordinate].get());
		td->notify(goals[coordinate].get());
		cout << "You have achieved Goal " << coordinate << "." << endl;
	}
}


// loops through students when a 7 is rolled and checks if
// the student will lose half their resources
void Board::loseResourcesGeese() {
  for(auto const &student: students){
    student->loseResources();
  }
}

// moves geese to a coordinate on the board,
// updating geeseAt
void Board::moveGeese(int coordinates) {
  if(geeseAt != -1){
    this->tiles[geeseAt]->toggleGeese();
  }
  if(coordinates == geeseAt || coordinates > 18 || coordinates < 0){
    throw std::invalid_argument("Invalid coordinates");
  }
  geeseAt = coordinates;
  tiles[coordinates]->toggleGeese();
	td->notify(coordinates); // textdisplay
}

Player Board::whoWon() {
	int bluePoints = this->students[0]->getPoints();
	int redPoints = this->students[1]->getPoints();
	int orangePoints = this->students[2]->getPoints();
	int yellowPoints = this->students[3]->getPoints();
	if (bluePoints >= 10) {
		return Player::Blue;
	} else if (redPoints >= 10) {
		return Player::Red;
	} else if (orangePoints >= 10) {
		return Player::Orange;
	} else if (yellowPoints >= 10) {
		return Player::Yellow;
	} else {
		return Player::None;
	}
}

// Resets game, student data, but not board
void Board::Reset(){
	for(int i = 0; i < 4; i++){
		this->students[i]->Reset();
	}
}

void Board::saveGame(Player curTurn) {
  cout << "Please name your save file:" << endl;
	cout << ">";
  string name, studentPrint;
  cin >> name;
  ofstream saveFile(name + ".txt"); // change this to date and time
  if (curTurn == Player::Blue) {
  	studentPrint = "blue";
  } else if (curTurn == Player::Red) {
  	studentPrint = "red";
  } else if (curTurn == Player::Orange) {
  	studentPrint = "orange";
  } else { // curTurn == Player::Orange
  	studentPrint = "yellow";
  }
	if (saveFile.is_open()) {
		saveFile << studentPrint << endl;
		saveFile << this->students[0]->printStudent() << endl;
		saveFile << this->students[1]->printStudent() << endl;
		saveFile << this->students[2]->printStudent() << endl;
		saveFile << this->students[3]->printStudent() << endl;
		saveFile << this->savePrint() << endl;
		saveFile << this->geeseAt << endl;
	}
	saveFile.close();
}

void Board::saveGameEof(Player curTurn, string name) {
	string studentPrint;
  ofstream saveFile(name + ".txt"); // change this to date and time
  if (curTurn == Player::Blue) {
  	studentPrint = "blue";
  } else if (curTurn == Player::Red) {
  	studentPrint = "red";
  } else if (curTurn == Player::Orange) {
  	studentPrint = "orange";
  } else { // curTurn == Player::Orange
  	studentPrint = "yellow";
  }
	if (saveFile.is_open()) {
		saveFile << studentPrint << endl;
		saveFile << this->students[0]->printStudent() << endl;
		saveFile << this->students[1]->printStudent() << endl;
		saveFile << this->students[2]->printStudent() << endl;
		saveFile << this->students[3]->printStudent() << endl;
		saveFile << this->savePrint() << endl;
		saveFile << this->geeseAt << endl;
	}
	saveFile.close();
}



// 0 3 1 10 3 5 1 4 5 7 3 10 2 11 0 3 3 8 0 2 0 6 1 8 4 12 1 5 4 11 2 4 4 6 2 9 2 9
//  0 representing CAFFEINE, 1 representing LAB, 2 representing LECTURE, 3 representing STUDY, 4 representing TUTORIAL, and 5 representing NETFLIX

void Board::loadGame(string loadFile, Player *whoseTurn) {
	if (loadFile == "default") {	return;	}
	int lineNumber = 1;
	string line;
	ifstream saveFile(loadFile + ".txt");
	if (saveFile.is_open()) {
		while (getline(saveFile, line)) {
			if (lineNumber == 1) {
				if (line == "blue") { *whoseTurn = Player::Blue; } 
				else if (line == "red") { *whoseTurn = Player::Red; } 
				else if (line == "orange") { *whoseTurn = Player::Orange; } 
				else { // line == "yellow" 
					*whoseTurn = Player::Yellow;
				}
			} else if (lineNumber == 2) {
				stringstream lineStream;
  				lineStream << line;
  				string inputType = "caffeine"; // either resource, goal or criterion
  				while (!lineStream.eof()) {
					string num;
    					lineStream >> num;
    					if (inputType == "caffeine") {
						students[0]->updateResources(Resource::Caffeine, stoi(num));
      						inputType = "lab";
    					} else if (inputType == "lab") {
    						students[0]->updateResources(Resource::Lab, stoi(num));
      						inputType = "lecture";
    					} else if (inputType == "lecture") {
    						students[0]->updateResources(Resource::Lecture, stoi(num));
      						inputType = "study";
    					} else if (inputType == "study") {
    						students[0]->updateResources(Resource::Study, stoi(num));
      						inputType = "tutorial";
    					} else if (inputType == "tutorial") {
    						students[0]->updateResources(Resource::Tutorial, stoi(num));
    						inputType = "null";
    					} else if (num == "g") {
      						inputType = "goal";
    					} else if (num == "c") {
      						inputType = "criterion";
    					} else if (inputType == "goal") {
						goals[stoi(num)]->updateOccupant(students[0].get());
						students[0]->updateGoal(goals[stoi(num)].get());
						td->notify(goals[stoi(num)].get());
    					} else if (inputType == "criterion") {
						int criterionType;
    						lineStream >> criterionType;
    						criterion[stoi(num)]->updateOccupant(students[0].get());
						students[0]->updateCriterion(criterion[stoi(num)].get());
						if (criterionType == 2) {
							criterion[stoi(num)]->upgrade();
      						} else if (criterionType == 3) {
							criterion[stoi(num)]->upgrade();
							criterion[stoi(num)]->upgrade();
						}
						td->notify(criterion[stoi(num)].get());

					}
				}
			} else if (lineNumber == 3) {
				stringstream lineStream;
  				lineStream << line;
				string inputType = "caffeine"; // either resource, goal or criterion
  				while (!lineStream.eof()) {
					string num;
    					lineStream >> num;
    					if (inputType == "caffeine") {
						students[1]->updateResources(Resource::Caffeine, stoi(num));
      						inputType = "lab";
					} else if (inputType == "lab") {
    						students[1]->updateResources(Resource::Lab, stoi(num));
      						inputType = "lecture";
    					} else if (inputType == "lecture") {
    						students[1]->updateResources(Resource::Lecture, stoi(num));
      						inputType = "study";
    					} else if (inputType == "study") {
    						students[1]->updateResources(Resource::Study, stoi(num));
      						inputType = "tutorial";
    					} else if (inputType == "tutorial") {
    						students[1]->updateResources(Resource::Tutorial, stoi(num));
    						inputType = "null";
    					} else if (num == "g") {
      						inputType = "goal";
    					} else if (num == "c") {
      						inputType = "criterion";
    					} else if (inputType == "goal") {
      						goals[stoi(num)]->updateOccupant(students[1].get());
						students[1]->updateGoal(goals[stoi(num)].get());
						td->notify(goals[stoi(num)].get());
    					} else if (inputType == "criterion") {
    						int criterionType;
    						lineStream >> criterionType;
     						criterion[stoi(num)]->updateOccupant(students[1].get());
						students[1]->updateCriterion(criterion[stoi(num)].get());
						td->notify(criterion[stoi(num)].get());
      						if (criterionType == 2) {
							criterion[stoi(num)]->upgrade();
      						} else if (criterionType == 3) {
      							criterion[stoi(num)]->upgrade();
      							criterion[stoi(num)]->upgrade();
						}
						td->notify(criterion[stoi(num)].get());
					}
				}
			} else if (lineNumber == 4) {
				stringstream lineStream;
  				lineStream << line;
  				string inputType = "caffeine"; // either resource, goal or criterion
  				while (!lineStream.eof()) {
					string num;
    					lineStream >> num;
    					if (inputType == "caffeine") {
						students[2]->updateResources(Resource::Caffeine, stoi(num));
      						inputType = "lab";
    					} else if (inputType == "lab") {
    						students[2]->updateResources(Resource::Lab, stoi(num));
      						inputType = "lecture";
    					} else if (inputType == "lecture") {
    						students[2]->updateResources(Resource::Lecture, stoi(num));
      						inputType = "study";
    					} else if (inputType == "study") {
    						students[2]->updateResources(Resource::Study, stoi(num));
      						inputType = "tutorial";
    					} else if (inputType == "tutorial") {
    						students[2]->updateResources(Resource::Tutorial, stoi(num));
    						inputType = "null";
    					} else if (num == "g") {
      						inputType = "goal";
    					} else if (num == "c") {
     			 			inputType = "criterion";
    					} else if (inputType == "goal") {
    						goals[stoi(num)]->updateOccupant(students[2].get());
						students[2]->updateGoal(goals[stoi(num)].get());
						td->notify(goals[stoi(num)].get());
					} else if (inputType == "criterion") {
    						int criterionType;
    						lineStream >> criterionType;
      						criterion[stoi(num)]->updateOccupant(students[2].get());
						students[2]->updateCriterion(criterion[stoi(num)].get());
      						if (criterionType == 2) {
							criterion[stoi(num)]->upgrade();
      						} else if (criterionType == 3) {
      							criterion[stoi(num)]->upgrade();
      							criterion[stoi(num)]->upgrade();
						}
						td->notify(criterion[stoi(num)].get());
					}
				}
			} else if (lineNumber == 5) {
				stringstream lineStream;
  				lineStream << line;
  				string inputType = "caffeine"; // either resource, goal or criterion
  				while (!lineStream.eof()) {
					string num;
    					lineStream >> num;
    					if (inputType == "caffeine") {
						students[3]->updateResources(Resource::Caffeine, stoi(num));
      						inputType = "lab";
    					} else if (inputType == "lab") {
    						students[3]->updateResources(Resource::Lab, stoi(num));
      						inputType = "lecture";
    					} else if (inputType == "lecture") {
    						students[3]->updateResources(Resource::Lecture, stoi(num));
      						inputType = "study";
    					} else if (inputType == "study") {
    						students[3]->updateResources(Resource::Study, stoi(num));
      						inputType = "tutorial";
    					} else if (inputType == "tutorial") {
    						students[3]->updateResources(Resource::Tutorial, stoi(num));
    						inputType = "null";
    					} else if (num == "g") {
      						inputType = "goal";
    					} else if (num == "c") {
      						inputType = "criterion";
    					} else if (inputType == "goal") {
						goals[stoi(num)]->updateOccupant(students[3].get());
						students[3]->updateGoal(goals[stoi(num)].get());
						td->notify(goals[stoi(num)].get());
    					} else if (inputType == "criterion") {
    						int criterionType;
    						lineStream >> criterionType;
      						criterion[stoi(num)]->updateOccupant(students[3].get());
						students[3]->updateCriterion(criterion[stoi(num)].get());
      						if (criterionType == 2) {
							criterion[stoi(num)]->upgrade();
      						} else if (criterionType == 3) {
      							criterion[stoi(num)]->upgrade();
      							criterion[stoi(num)]->upgrade();
						}
						td->notify(criterion[stoi(num)].get());
					}
				}
			} else if (lineNumber == 6) {
				stringstream lineStream;
				lineStream << line;
				while (!lineStream.eof()) {
					int type;
					Resource resourceType;
					int value;
					int location = 0;
					lineStream >> type;
					lineStream >> value;
					if (type == 0) {
						resourceType = Resource::Caffeine;
					} else if (type == 1) {
						resourceType = Resource::Lab;
					} else if (type == 2) {
						resourceType = Resource::Lecture;
					} else if (type == 3) {
						resourceType = Resource::Study;
					} else if (type == 4) {
						resourceType = Resource::Tutorial;
					} else {
						resourceType = Resource::Netflix;
					}
					tiles[location] = make_unique<Tile>(value, resourceType);
					++location;
				}
			} else if (lineNumber == 7) {
				int intGeeseAt = stoi(line);
			//	if (geeseAt != -1) {
				/*	if(geeseAt != intGeeseAt){
						tiles[geeseAt]->toggleGeese();
					} */
				if(intGeeseAt != -1){
					td->notify(intGeeseAt); // prints geese on board
					geeseAt = intGeeseAt;
					tiles[geeseAt]->toggleGeese();
				}
				//}
			}
			++lineNumber;
		}
		saveFile.close();
	}
}

// fills in an empty vector of vector of criterion and
// a vector of vector goals depending on how many layers there are
// in the board
void Board::rowSetup(const int n, vector<vector<unique_ptr<Criterion>>> &criterion, vector<vector<unique_ptr<Goal>>> &goal) {
	criterion.resize(8 * n + 5);
	goal.resize(8 * n + 5);

	int patternedRow = (2 * n) + 2;
	int goalNo = 0;
	int criterionNo = 0;
	int k = 1; // horizontal goal counter
	for (int i = 0; i < patternedRow; ++i) {	// first set of special rows
		if (i % 2 == 0) {
			for (int j = 0; j < k; ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
			for (int j = 0; j < (2 * k); ++j) {
				criterion[i].emplace_back(make_unique<Criterion>(criterionNo));
				++criterionNo;
			}
		}
		else {
			for (int j = 0; j < (2 * k); ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
			++k;
		}
	}

	int secondPatternedRow = (6 * n) + 3;
	int temp = n; // number of goal in patternedRow
	for (int i = patternedRow; i < secondPatternedRow; ++i) {
		if (i % 2 == 0) {
			for (int j = 0; j < temp; ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
			if (temp == n) { ++temp; }
			else { --temp; }
			for (int j = 0; j < ((2 * n) + 2); ++j) {
				criterion[i].emplace_back(make_unique<Criterion>(criterionNo));
				++criterionNo;
			}
		}
		else {
			for (int j = 0; j < ((2 * n) + 2); ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
		}
	}

	--k; // horizontal goal counter
	for (int i = secondPatternedRow; i < (8 * n) + 5; ++i) {
		if (i % 2 != 0) {
			for (int j = 0; j < (2 * k); ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
		}
		else {
			for (int j = 0; j < k; ++j) {
				goal[i].emplace_back(make_unique<Goal>(goalNo));
				++goalNo;
			}
			for (int j = 0; j < (2 * k); ++j) {
				criterion[i].emplace_back(make_unique<Criterion>(criterionNo));
				++criterionNo;
			}
			--k;
		}
	}
}

// updates all the criterion and goal vector of vectors with their
// fields that require pointers to other criterion or goals
void Board::update(const int n, vector<vector<unique_ptr<Criterion>>> &criterion, vector<vector<unique_ptr<Goal>>> &goal) {
	int patternedRow = (2 * n) + 2;

	int goalCounter = 1;
	for (int i = 0; i < patternedRow; ++i) {
		if (i % 2 == 0) {
			int c = 0;
			for (int g = 0; g < goalCounter; ++g) { // traversing through the goals in row i
				goal[i][g]->addNeighbor(criterion[i][c].get());
				++c;
				goal[i][g]->addNeighbor(criterion[i][c].get());
				++c;
			}
			++goalCounter;
		}
		else {
			//adding the first criterion to goal
			int size = goal[i].size();
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g].get());
				//cout << criterion[i + 1][g + 1]->getCoordinate() << endl;
				if (i == patternedRow - 1) {
					goal[i][g]->addNeighbor(criterion[i + 1][g].get());
				}
				else {
					goal[i][g]->addNeighbor(criterion[i + 1][g + 1].get());
				}
			}
		}
	}

	// entering patternedRow
	int secondPatternedRow = (6 * n) + 3;
	for (int i = patternedRow; i <= secondPatternedRow; ++i) {
		int size = goal[i].size();
		if (i % 2 == 0) {
			if (size == n) {
				int cCounter = 1;
				for (int g = 0; g < size; ++g) {
					goal[i][g]->addNeighbor(criterion[i][cCounter].get());
					++cCounter;
					goal[i][g]->addNeighbor(criterion[i][cCounter].get());
					++cCounter;
				}
			}
			else {
				int cCounter = 0;
				for (int g = 0; g < size; ++g) {
					goal[i][g]->addNeighbor(criterion[i][cCounter].get());
					++cCounter;
					goal[i][g]->addNeighbor(criterion[i][cCounter].get());
					++cCounter;
				}
			}
		}
		else {
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g].get());
				goal[i][g]->addNeighbor(criterion[i + 1][g].get());
			}
		}
	}

	int gCounter = n + 1;
	for (int i = secondPatternedRow + 1; i < (8 * n) + 5; ++i) {
		int size = goal[i].size();
		if (i % 2 == 0) {
			int c = 0;
			for (int g = 0; g < gCounter; ++g) {
				goal[i][g]->addNeighbor(criterion[i][c].get());
				++c;
				goal[i][g]->addNeighbor(criterion[i][c].get());
				++c;
			}
			--gCounter;
		}
		else {
			for (int g = 0; g < size; ++g) {
				goal[i][g]->addNeighbor(criterion[i - 1][g + 1].get());
				goal[i][g]->addNeighbor(criterion[i + 1][g].get());
			}
		}
	}
}

void Board::setDice(string type) {
	dice = type;
}

// rolls either fair or loaded die
// check if 7 is rolled and sets geese
void Board::roll(Player curTurn) {
	int rolledval;
	Dice *die = Dice::make_dice(dice);
	if (dice == "fair") {
		//rolledval = die.roll();
	}
	else if (dice == "load") {
		int toLoad;
		while (true) {
			cout << "Input a roll between 2 and 12:" << endl;
			cout << ">";
			cin >> toLoad;
			if (toLoad < 2 || toLoad > 12) {
				cout << "Invalid roll." << endl;
				cout << ">";
				continue;
			}
			break;
		}
		die->setDie(toLoad);
		//rolledval = die.roll();
	}
	rolledval = die->roll();
	// checks if 7 is rolled
	// if it is, call geese
	if(rolledval == 7){
		bool lost = false;
		for(int i = 0; i < 4; i++){
			if(this->students[i]->numResources() >= 10){
				lost = true;
			}
		}

		if(!lost){
			cout << "No resources were lost to the Geese." << endl;
		}
		else{
			this->loseResourcesGeese();
		}

		cout << "Choose where to place the Geese." << endl;
		cout << ">";
		int moveto;
		cin >> moveto;
		while((moveto == geeseAt) || (moveto > 18) || (moveto < 0)){
			cout << "Please input an integer between 0 and 18 inclusive" << endl;
			cout << ">";
			cin >> moveto;
		}
		this->moveGeese(moveto);
		//Student <colour1> can choose to steal from [students].

		string str = this->tiles[moveto]->playersToStealFrom(curTurn);
	//	cout << "after sketch function" << endl; // DEBUG STATEMENT

		if(str == ""){
			cout << "Student " << curTurn << " has no students to steal from." << endl;
		}
		else{
			vector<string> onTile;
			istringstream ss(str);
			string token;

			while(getline(ss, token, ',')) {
			  onTile.emplace_back(token); // filling onTile
			}

			cout << "Student " << curTurn <<" can choose to steal from " << str << "." << endl;
			cout << "Choose a student to steal from." << endl;
			cout << ">";

			string stealFrom;
			bool isvalid = false;
			while(!isvalid) {
				cin >> stealFrom;
				for(int i = 0; i < onTile.size(); i++){
					if(onTile[i] == stealFrom){
						isvalid = true;
					}
				}
				if(!isvalid){
					cout << "Invalid input. " << "Student " << curTurn <<" can choose to steal from " << str << "." << endl;
					cout << ">";
				}
			}

			int stealerIndex;
			int stolenfromIndex;

			if(curTurn == Player::Blue){
				stealerIndex = 0;
			}
			else if(curTurn == Player::Red){
				stealerIndex = 1;
			}
			else if(curTurn == Player::Orange){
				stealerIndex = 2;
			}
			else if(curTurn == Player::Yellow){
				stealerIndex = 3;
			}

			if(stealFrom == "Blue"){
				stolenfromIndex = 0;
			}
			else if(stealFrom == "Red"){
				stolenfromIndex = 1;
			}
			else if(stealFrom == "Orange"){
				stolenfromIndex = 2;
			}
			else if(stealFrom == "Yellow"){
				stolenfromIndex = 3;
			}

			// steal resources
			students[stealerIndex]->stealResources(*students[stolenfromIndex]);
		}
	}


	// if 7 IS NOT rolled
	// checking tiles that have same value as rolled value
	// and sending resources
	else{
		bool sent = false;
		for(int i = 0; i < 19; i++){
			if(tiles[i]->getValue() == rolledval){
				if(tiles[i]->sendResources()) {
					sent = true;
				}
			}
		}
		if(!sent){
			cout << "No students gained resources." << endl;
		}
	}
}

void Board::print() {
	cout << *td;
}

string Board::savePrint() {
	string toPrint = "";
	for (int i = 0; i < 19; ++i) {
		if (toPrint != "") {
			toPrint += " "; // {Caffeine, Lab, Lecture, Study, Tutorial, Netflix, None};
		}
		Resource toAppend = tiles[i]->getResource();
		if (toAppend == Resource::Caffeine) {
			toPrint += "0";
		} else if (toAppend == Resource::Lab) {
			toPrint += "1";
		} else if (toAppend == Resource::Lecture) {
			toPrint += "2";
		} else if (toAppend == Resource::Study) {
			toPrint += "3";
		} else if (toAppend == Resource::Tutorial) {
			toPrint += "4";
		} else if (toAppend == Resource::Netflix) {
			toPrint += "5";
		}
		toPrint += " ";
		toPrint += to_string(tiles[i]->getValue());
	}
	return toPrint;
}

void Board::status() {
	for (auto const& student: this->students) {
		student->printStatus();
	}
}

void Board::blueStatus(){
	this->students[0]->printStatus();
}

void Board::redStatus(){
	this->students[1]->printStatus();
}

void Board::orangeStatus(){
	this->students[2]->printStatus();
}

void Board::yellowStatus(){
	this->students[3]->printStatus();
}

void Board::criteria(Player player) {
	int toPrint;
	if (player == Player::Blue) {
		toPrint = 0;
	} else if (player == Player::Red) {
		toPrint = 1;
	} else if (player == Player::Orange) {
		toPrint = 2;
	} else { // player == Player::Yellow
		toPrint = 3;
	}
	cout << this->students[toPrint]->printCriteria() << endl;
}

void Board::trade(Player tradeFrom, Player tradeWith, Resource give, Resource take) {
	Student *player1;
	Student *player2;
	if (tradeFrom == Player::Blue) {
		player1 = students[0].get();
	} else if (tradeFrom == Player::Red) {
		player1 = students[1].get();
	} else if (tradeFrom == Player::Orange) {
		player1 = students[2].get();
	} else { // player == Player::Yellow
		player1 = students[3].get();
	}
	if (tradeWith == Player::Blue) {
		player2 = students[0].get();
	} else if (tradeWith == Player::Red) {
		player2 = students[1].get();
	} else if (tradeWith == Player::Orange) {
		player2 = students[2].get();
	} else if (tradeWith == Player::Yellow) {
		player2 = students[3].get();
	}
	else {
		player1->trade(give, take);
		return;
	}
	player1->trade(player2, give, take);
}

void Board::criterionAdderHelper(int &iter, const int tileNo) {
	for (int i = 0; i < 2; ++i) {
		tiles[tileNo]->addCriterion(criterion[iter].get());
		++iter;
	}
}

void Board::updateCriterionsInTile(const int n) {
	//int totalTiles = (3 * n * n) + (3 * n) + 1;

	int patternStartsAt = (n * (n + 1)) / 2;	// Tile No.
	double secondPattern = ((n * n) / (double)2) + ((3 * n) / (double)2) + 1;
	int two_n = 2 * patternStartsAt;    		// counter
	int two_n2 = 2 * secondPattern + 1; 		// counter
	int start;                          		// counter
	for (int k = 0; k < n + 1; ++k) {			// loop through the rows
		int starting = patternStartsAt;
		if (k != 0) { starting += (2 * n + 1) * k; }
		for (int i = 0; i < 3; ++i) { 			// loop through the columns
			for (int j = 0; j < n + 1; ++j) {	// loop through the tiles in a row k
				criterionAdderHelper(two_n, starting + j);
			}
		}
		two_n -= 2 * n + 2;
		start = starting;
	}
	for (int k = 0; k < n; ++k) {
		int starting = secondPattern;
		if (k != 0) { starting += (2 * n + 1) * k; }
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < n; ++j) {
				criterionAdderHelper(two_n2, starting + j);
			}
			two_n2 += 2;
		}
		two_n2 -= 2 * n + 2;
	}

	// FIRST END CASE

	vector<vector<int>> row; // helper top row
	row.resize(n + 1);
	int tileNo = 0;
	for (int k = 0; k < n + 1; ++k) {
		for (int j = 0; j < k + 1; ++j) {
			row[k].emplace_back(move(tileNo));
			++tileNo;
		}
	}

	int vert = 0;
	for (int k = 0; k < n + 1; ++k) {
		int vert2 = vert + 1;
		if (k == n) {
			int vert3 = vert2 + 1;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) { // row where Pattern starts
				criterionAdderHelper(vert2, *j);
			}
			if (k > 1) {
				for (auto j = row[k - 2].begin(); j != row[k - 2].end(); ++j) {
					criterionAdderHelper(vert3, *j);
				}
				vert3 += 3;
				for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
					criterionAdderHelper(vert3, *j);
				}
				break;
			}
			vert2 += 2;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				criterionAdderHelper(vert2, *j);
			}
			break;
		}
		for (auto j = row[k].begin(); j != row[k].end(); ++j) {
			criterionAdderHelper(vert, *j);
		}
		if (k >= 2) {
			int vert3 = vert2 + 1;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				criterionAdderHelper(vert2, *j);
			}
			for (auto j = row[k - 2].begin(); j != row[k - 2].end(); ++j) {
				criterionAdderHelper(vert3, *j);
			}
		}
		else if (k == 1) {
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				criterionAdderHelper(vert2, *j);
			}
		}
	}

	// SECOND END CASE

	vector<vector<int>> bottomRow; // helper bottom row
	bottomRow.resize(n);

	int secondEndCase = start + n + 1;
	int counter = n;
	int start2 = two_n + 1;
	int start3 = start2 + 1;
	for (int k = n - 1; k >= 0; --k) { // fix limit
		for (int j = 0; j < counter; ++j) {
			bottomRow[k].emplace_back(move(secondEndCase));
			++secondEndCase;
		}
		--counter;
	}

	int temp = two_n - (2 * n) - 1;
	for (auto j = bottomRow[n - 1].begin(); j != bottomRow[n - 1].end(); ++j) { // for special end case
		criterionAdderHelper(temp, *j);
		criterionAdderHelper(start2, *j);
	}

	if (n - 2 >= 0) {
		for (auto j = bottomRow[n - 2].begin(); j != bottomRow[n - 2].end(); ++j) {
			criterionAdderHelper(start3, *j);
		}
	}
	++start2;

	int temp2 = start2 + 1; // for k - 1
	for (int k = n - 1; k >= 0; --k) {
		int temp3 = temp2 + 1; // for  k - 2
		for (auto j = bottomRow[k].begin(); j != bottomRow[k].end(); ++j) {
			criterionAdderHelper(start2, *j);
		}
		if (k - 1 >= 0) {
			for (auto j = bottomRow[k - 1].begin(); j != bottomRow[k - 1].end(); ++j) {
				criterionAdderHelper(temp2, *j);
			}
			if (k - 2 >= 0) {
				for (auto j = bottomRow[k - 2].begin(); j != bottomRow[k - 2].end(); ++j) {
					criterionAdderHelper(temp3, *j);
				}
			}
		}
	}
}

void Board::updateCriterionsNeighbor() {
	int size = criterion.size();
	for (int i = 0; i < size; ++i) {
		criterion[i]->addNeighbor();
	}
}
