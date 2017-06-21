#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "Utils/Utilities.h"

using namespace std;

//Protos
vector<int> hardcodedSplit(string s);
bool checkTriangle(int s1, int s2, int s3);
//Was going to template this for the lolz and for practice but I'm too lazy to
int maximum(int n1, int n2);
int maximum(int n1, int n2, int n3);


int main() {

	vector<string> text = Utilities::ReadFile("Day3/Input.txt");
	//vector<string> text = {"  5  25  10", "  10  5  25" ,"  25  10  5"}; //Manual for debugging
	
	
	unsigned int counter = 0;
	
	//This was part 1
	/*
	vector<int> rawNumbers;
	
	for(auto &elem : text){
		//Utilities::trimString(elem); // Shouldn't even be needed here
		rawNumbers = hardcodedSplit(elem); //Dumped Utilities::splitString for this hardcoded function because it was inconsistent
		
		counter += (checkTriangle(rawNumbers[0], rawNumbers[1], rawNumbers[2]) ? 1 : 0);
	}
	*/
	
	//This is now for part 2
	vector<int> col1;
	vector<int> col2;
	vector<int> col3;
	vector<int> rawNumbers;
	
	for(auto const &line : text){
		rawNumbers = hardcodedSplit(line);
		col1.push_back(rawNumbers[0]);
		col2.push_back(rawNumbers[1]);
		col3.push_back(rawNumbers[2]);
	}
	
	for(unsigned int i = 0; i < col1.size(); i+=3){
		counter += (checkTriangle(col1[i], col1[i+1], col1[i+2]));
		counter += (checkTriangle(col2[i], col2[i+1], col2[i+2]));
		counter += (checkTriangle(col3[i], col3[i+1], col3[i+2]));
	}
	
	cout << "There are " << counter << " possible triangles, out of " << col1.size() << " proposed triangles." << endl;

	return 0;
}

vector<int> hardcodedSplit(string s){
	vector<int> output;
	int temp;
	
	s = s.substr(s.find_first_not_of(" "));
	temp = stoi(s.substr(0, s.find(" ")));
	output.push_back(temp);
	
	s = s.substr(s.find(" "));
	s = s.substr(s.find_first_not_of(" "));
	temp = stoi(s.substr(0, s.find(" ")));
	output.push_back(temp);
	
	s = s.substr(s.find(" "));
	s = s.substr(s.find_first_not_of(" "));
	temp = stoi(s);
	output.push_back(temp);
	
	return output;
}

bool checkTriangle(int s1, int s2, int s3){

	int sum = s1 + s2 + s3;
	int max = maximum(s1, s2, s3);
	return (sum-max > max);
}

int maximum(int n1, int n2){ return (n1 > n2 ? n1 : n2); }

int maximum(int n1, int n2, int n3){ return maximum(maximum(n1,n2),n3); }
