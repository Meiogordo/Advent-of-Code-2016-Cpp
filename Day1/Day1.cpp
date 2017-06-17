#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
	
	vector<string> rawText = readInput();
	vector<string> splitText = splitString(rawText[0], ",");


	return 0;
}

const vector<string>& readInput(string txtfilename = "Input.txt") {
	ifstream in(txtfilename);
	vector<string> output;
	string temp;

	while (getline(in, temp)) {
		output.push_back(temp);
	}

	return output;
}

vector<string> splitString(string input, string splitter) {
	vector<string> output;

	//while the splitter sequence exists in input
	while (input.find(splitter) != string::npos) {
		output.push_back(input.substr(0, input.find(splitter)));
		input = input.substr(input.find(splitter) + splitter.length() + 1);
	}

	//Push back the remainder, or the whole string if no ocurrence of splitter exists
	output.push_back(input);

	return output;
}