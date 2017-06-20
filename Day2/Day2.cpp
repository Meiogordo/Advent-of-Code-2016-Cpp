#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Utils/Utilities.h"

using namespace std;

//Protos
void interpretLine(pair<int, int> &pos, string instructions);
void interpretChar(pair<int, int> &pos, char instruction);
void interpretCharP2(pair<int, int> &pos, char instruction);


int main() {

	//const vector<vector<int>> keypad = { {1,2,3}, {4,5,6}, {7,8,9} }; //Old keypad, do not entirely get why this one fails lol
	//const vector<vector<int>> keypad = { {1,4,7},{2,5,8},{3,6,9} }; // This one works

	//Keypad:
	// 1 2 3
	// 4 5 6
	// 7 8 9

	//P2 Keypad:
	//     1
	//   2 3 4
	// 5 6 7 8 9
	//   A B C
	//     D

	//Defining p2 keypad - considering 7 (0,0) and there can be negative coordinates
	map<int, map<int, char>> p2Keypad;
	p2Keypad[0][0] = '7';
	p2Keypad[0][-1] = 'B';
	p2Keypad[0][-2] = 'D';
	p2Keypad[0][1] = '3';
	p2Keypad[0][2] = '1';

	p2Keypad[-1][1] = '2';
	p2Keypad[-1][0] = '6';
	p2Keypad[-1][-1] = 'A';

	p2Keypad[-2][0] = '5';

	p2Keypad[1][1] = '4';
	p2Keypad[1][0] = '8';
	p2Keypad[1][-1] = 'C';

	p2Keypad[2][0] = '9';

	pair<int, int> keypadPos = { -2,0 }; //Starts at 5 (was 1,1 for P1, now is -2,0)

	//vector<string> text = { "ULL","RRDDD","LURDL","UUUUD" }; //Manual override for example testing
	vector<string> text = Utilities::ReadFile("Day2/Input.txt");

	for (int i = 0; i < text.size(); ++i) {
		interpretLine(keypadPos, text[i]);
		cout << "New keypad press: " << p2Keypad[keypadPos.first][keypadPos.second] << endl;
	}

	return 0;
}

void interpretLine(pair<int, int> &pos, string instructions) {

	for (int i = 0; i < instructions.length(); ++i) {
		//interpretChar(pos, instructions[i]);
		interpretCharP2(pos, instructions[i]);
	}

}

void interpretChar(pair<int, int> &pos, char instruction) {
	switch (instruction) {
	case 'U':
		if (pos.second > 0)
			--pos.second;
		break;
	case 'R':
		if (pos.first < 2)
			++pos.first;
		break;
	case 'D':
		if (pos.second < 2)
			++pos.second;
		break;
	case 'L':
		if (pos.first > 0)
			--pos.first;
		break;
	default:
		cout << "Uh oh, spaghetti-Ohs!" << endl;
		exit(1);
	}
}

void interpretCharP2(pair<int, int> &pos, char instruction) {
	switch (instruction) {
	case 'U':
		switch (pos.second) {
		case 0:
			if (pos.first != -2 && pos.first != 2)
				++pos.second;
			break;
		case 1:
			if (pos.first != -1 && pos.first != 1)
				++pos.second;
			break;
		case 2:
			break;
		default:
			++pos.second;
			break;
		}
		break;
	case 'R':
		switch (pos.first) {
		case 0:
			if (pos.second != -2 && pos.first != 2)
				++pos.first;
			break;
		case 1:
			if (pos.second != -1 && pos.second != 1)
				++pos.first;
			break;
		case 2:
			break;
		default:
			++pos.first;
			break;
		}
		break;
	case 'D':
		switch (pos.second) {
		case 0:
			if (pos.first != -2 && pos.first != 2)
				--pos.second;
			break;
		case -1:
			if (pos.first != -1 && pos.first != 1)
				--pos.second;
			break;
		case -2:
			break;
		default:
			--pos.second;
			break;
		}
		break;
	case 'L':
		switch (pos.first) {
		case 0:
			if (pos.second != -2 && pos.first != 2)
				--pos.first;
			break;
		case -1:
			if (pos.second != -1 && pos.second != 1)
				--pos.first;
			break;
		case -2:
			break;
		default:
			--pos.first;
			break;
		}
		break;
	default:
		cout << "Uh oh, spaghetti-Ohs!" << endl;
		exit(1);
	}
}
