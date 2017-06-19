#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "../Utilities.h"

using namespace std;

//Protos
void switchDirection(char Rotation, char &currDirection);
void walk(const char &currDirection, pair<int, int> &currPos, const int &walkAmout);

int main() {
	
	vector<string> rawText = Utilities::ReadFile("Input-copy.txt");
	//vector<string> rawText(1, "R5, L5, R5, R3"); //Manual override

	//Splitting text at each ","
	vector<string> splitText = Utilities::splitString(rawText[0], ",");
	//Trimming text
	for (auto &el : splitText) {
		Utilities::trimString(el);
	}

	//Now splitText holds only "cells" of R/L and int

	//Initializing starting position and rotation
	pair<int, int> currPos = { 0,0 }; //(x,y)
	char direction = 'N';

	for (unsigned int i = 0; i < splitText.size(); ++i) {
		switchDirection(splitText[i][0], direction);
		walk(direction, currPos, stoi(splitText[i].substr(1)));

		cout << "i: " << i << "\t" << splitText[i] << "\t" << "new pos: " << currPos.first << "|" << currPos.second << endl;
	}

	cout << "\n\n\n" << "Final pos: " << currPos.first << "|" << currPos.second;
	cout << "\nDistance walked: " << (abs(currPos.first) + abs(currPos.second)) << endl;

	return 0;
}

//Rotates
void switchDirection(char Rotation, char &currDirection) {
	switch (currDirection) {
	case 'N':
		currDirection = (Rotation == 'R') ? 'E' : 'W';
		break;
	case 'E':
		currDirection = (Rotation == 'R') ? 'S' : 'N';
		break;
	case 'S':
		currDirection = (Rotation == 'R') ? 'W' : 'E';
		break;
	case 'W':
		currDirection = (Rotation == 'R') ? 'N' : 'S';
		break;
	default:
		cout << "Poop nuggets! Something went terribly wrong!" << endl;
		break;
	}
}

//Walks
void walk(const char &currDirection, pair<int, int> &currPos, const int &walkAmout) {
	switch (currDirection) {
	case 'N':
		currPos.second += walkAmout;
		break;
	case 'E':
		currPos.first += walkAmout;
		break;
	case 'S':
		currPos.second -= walkAmout;
		break;
	case 'W':
		currPos.first -= walkAmout;
		break;
	default:
		cout << "Poop nuggets! Something went terribly wrong!" << endl;
		break;
	}
}