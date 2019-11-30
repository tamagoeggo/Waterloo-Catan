#include <iostream>
#include <vector>
#include <array>
using namespace std;

void emplacingBack(int &iter, vector<vector<int>> &v, const int tileNo) {
	for (int i = 0; i < 2; ++i) {
		v[tileNo].emplace_back(iter);
		++iter;
	}
}

vector<vector<int>> createBoard(const int n) {
	int totalTiles = (3 * n * n) + (3 * n) + 1;
	vector<vector<int>> tileList(totalTiles);
	int patternStartsAt = (n * (n + 1)) / 2; 					// Tile No.
	double secondPattern = ((n * n) / (double)2) + ((3 * n) / (double)2) + 1;
	int two_n = 2 * patternStartsAt;
	int two_n2 = 2 * secondPattern + 1;
	int start;
	for (int k = 0; k < n + 1; ++k) {		// loop through the rows
		int starting = patternStartsAt;
		if (k != 0) { starting += (2 * n + 1) * k; }
		for (int i = 0; i < 3; ++i) { 			// loop through the columns
			for (int j = 0; j < n + 1; ++j) {	// loop through the tiles in a row k
				//tileList[starting + j].emplace_back(two_n);
				//++two_n;
				//tileList[starting + j].emplace_back(two_n);
				//++two_n;
				emplacingBack(two_n, tileList, starting + j);
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
				//tileList[starting + j].emplace_back(two_n2);
				//++two_n2;
				//tileList[starting + j].emplace_back(two_n2);
				//++two_n2;
				emplacingBack(two_n2, tileList, starting + j);
			}
			two_n2 += 2;
		}
		two_n2 -= 2 * n + 2;
	}

	// FIRST END CASE
	
	vector<vector<int>> row; // top row
	row.resize(n + 1);
	int tileNo = 0;
	for (int k = 0; k < n + 1; ++k) {
		cout << "Row " << k << " has ";
		for (int j = 0; j < k + 1; ++j) {
			cout << tileNo << " ";
			row[k].emplace_back(tileNo);
			++tileNo;
		}
		cout << endl;
	}

	int vert = 0;
	for (int k = 0; k < n + 1; ++k) {
		int vert2 = vert + 1;
		if (k == n) {
			int vert3 = vert2 + 1;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) { // row where Pattern starts
				//for (int i = 0; i < 2; ++i) {
				//	tileList[*j].emplace_back(vert2);
				//	++vert2;
				//}
				emplacingBack(vert2, tileList, *j);
			}
			if (k > 1) {
				for (auto j = row[k - 2].begin(); j != row[k - 2].end(); ++j) {
					for (int i = 0; i < 2; ++i) {
						tileList[*j].emplace_back(vert3);
						++vert3;
					}
				}
				vert3 += 3;
				for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
					for (int i = 0; i < 2; ++i) {
						tileList[*j].emplace_back(vert3);
						++vert3;
					}
				}
				break;
			}
			vert2 += 2;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				for (int i = 0; i < 2; ++i) {
					tileList[*j].emplace_back(vert2);
					++vert2;
				}
			}
			break;
		}
		for (auto j = row[k].begin(); j != row[k].end(); ++j) {
			for (int i = 0; i < 2; ++i) {
				tileList[*j].emplace_back(vert);
				++vert;
			}
		}
		if (k >= 2) {
			int vert3 = vert2 + 1;
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				for (int i = 0; i < 2; ++i) {
					tileList[*j].emplace_back(vert2);
					++vert2;
				}
			}
			for (auto j = row[k - 2].begin(); j != row[k - 2].end(); ++j) {
				for (int i = 0; i < 2; ++i) {
					tileList[*j].emplace_back(vert3);
					++vert3;
				}
			}
		}
		else if (k == 1) {
			for (auto j = row[k - 1].begin(); j != row[k - 1].end(); ++j) {
				for (int i = 0; i < 2; ++i) {
					tileList[*j].emplace_back(vert2);
					++vert2;
				}
			}
		}
	}

	// SECOND END CASE

	vector<vector<int>> bottomRow; // bottom row
	bottomRow.resize(n);
	//int lastTile = totalTiles - 1;
	int secondEndCase = start + n + 1;
	int counter = n;
	int start2 = two_n + 1;
	int start3 = start2 + 1;
	for (int k = n - 1; k >= 0; --k) { // fix limit
		//cout << "At Row " << k;
		for (int j = 0; j < counter; ++j) {
		//	cout << " " << secondEndCase;
			bottomRow[k].emplace_back(secondEndCase);
			++secondEndCase;
		}
		//cout << endl;
		--counter;
	}
	
	int temp = two_n - (2 * n) - 1;
	for (auto j = bottomRow[n - 1].begin(); j != bottomRow[n - 1].end(); ++j) { // for special end case
		for (int i = 0; i < 2; ++i) {
			tileList[*j].emplace_back(temp);
			++temp;
		}
		for (int i = 0; i < 2; ++i) {
			tileList[*j].emplace_back(start2);
			++start2;
		}
	}
	//++start2;

	if (n - 2 >= 0) {
		//int start3 = start2 + 1;
		cout << "Start3 is " << start3 << endl;
		for (auto j = bottomRow[n - 2].begin(); j != bottomRow[n - 2].end(); ++j) { 
			cout << "In Tile " << *j << endl;
			for (int i = 0; i < 2; ++i) {
				tileList[*j].emplace_back(start3);
				++start3;
			}
		}
	}
	++start2;
	
	int temp2 = start2 + 1; // for k - 1
	for (int k = n - 1; k >= 0; --k) {
		//int temp2 = start2 + 1;
		int temp3 = temp2 + 1; // for  k - 2
		cout << "Temp2 is " << temp2 << " and Temp3 is " << temp3 << endl;
		for (auto j = bottomRow[k].begin(); j != bottomRow[k].end(); ++j) {
			for (int i = 0; i < 2; ++i) {
				tileList[*j].emplace_back(start2);
				++start2;
			}
		}		
		if (k - 1 >= 0) {
			for (auto j = bottomRow[k - 1].begin(); j != bottomRow[k - 1].end(); ++j) {
				for (int i = 0; i < 2; ++i) {
					tileList[*j].emplace_back(temp2);
					++temp2;
				}
			}
			if (k - 2 >= 0) {
				cout << "In k - 2" << endl;
				for (auto j = bottomRow[k - 2].begin(); j != bottomRow[k - 2].end(); ++j) {
					for (int i = 0; i < 2; ++i) {
						tileList[*j].emplace_back(temp3);
						++temp3;
					}
				}
			}
		}
	}


	for (int m = 0; m < totalTiles; ++m) {
		cout << "Tile " << m << ":";
		for (auto j = tileList[m].begin(); j != tileList[m].end() ; ++j) {
			cout << " " << *j;
		}
		cout << endl;
	}
	cout << "Last criterion added is " << two_n << endl;
	cout << "Starting is at " << start << endl;
	return tileList;
}

int main() {
	int layer;
	cout << "Insert number of layers for board" << endl;
	cin >> layer;
	createBoard(layer);	
	return 1;
}
