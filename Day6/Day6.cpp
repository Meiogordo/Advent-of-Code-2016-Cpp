#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

#include "Utils/Utilities.h"

using namespace std;


//Protos
string findRealMessage(vector<string> messages);
bool sortfunc(const pair<char, unsigned int> &p1, const pair<char, unsigned int> &p2);
char mostcommonchar(const map<char, unsigned int> &m);


int main() {
	
	vector<string> text = Utilities::ReadFile("Day6/Input.txt");
	//vector<string> text = {"eedadn", "drvtee", "eandsr", "raavrd", "atevrs", "tsrnev", "sdttsa", "rasrtv", "nssdts", "ntnada", "svetve", "tesnvt", "vntsnd", "vrdear", "dvrsen", "enarar"}; //Manual for debugging
	
	cout << "The real message for the given input is: " << findRealMessage(text) << endl;
	
	return 0;
}

string findRealMessage(vector<string> messages){
	
	string output = "";
	
	map<unsigned int, map<char, unsigned int>> counter;
	
	for(unsigned int i = 0;  i < messages.size(); ++i){
	
		for(unsigned int j = 0; j < messages[i].size(); ++j){
			//Counts the jth char in the j position
			++counter[j][messages[i][j]];
		}
		
	}
	
	//assuming all messages have the same size which is true supposedly
	for(unsigned int i = 0; i < messages[0].size(); ++i){
		output.push_back(mostcommonchar(counter[i]));
	}
	
	return output;	
}

//For sorting the vector
bool sortfunc(const pair<char, unsigned int> &p1, const pair<char, unsigned int> &p2){
	if(p1.second == p2.second)
		return p1.first < p2.first;
	else
		return p1.second > p2.second;
}

//Gets the most common char in a <char,unsigned int> map
char mostcommonchar(const map<char, unsigned int> &m){
	//Copying the map to a vector
	vector<pair<char, unsigned int>> vec(m.begin(), m.end());
	
	//sorting the vector in descending order using sortfunc
	sort(vec.begin(), vec.end(), sortfunc);
	
	//The most common char is the first one
	return vec[0].first;
}
