#include <iostream>
#include <vector>
#include <string>

#include "Utils/Utilities.h"

using namespace std;


//Protos
bool checkTLS(string ip);
bool hasAbba(string str);
bool checkSSL(string ip);
vector<pair<char,char>> getABAs(const vector<string> &outers);
vector<pair<char,char>> getABAs(const string &str);
bool hasBAB(const vector<string> &inners, const vector<pair<char,char>> &ABAs);
bool hasBAB(const string &inner, const vector<pair<char,char>> &ABAs);

int main() {
	
	vector<string> text = Utilities::ReadFile("Day7/Input.txt");
	//vector<string> text = {"aaa[kek]eke","zazbz[bzb]cdb"}; //Manual for debugging
	
	//Changed tls to ssl only lol
	
	long unsigned int sslCounter = 0;
	
	for(auto const &ip : text){
		sslCounter += checkSSL(ip);
	}
	
	cout << "Out of " << text.size() << " IPv7 IPs, " << sslCounter << " support SSL" << endl;
	
	return 0;
}

bool checkTLS(string ip) {
	bool abbaOut = false, noAbbaIn = true; //The initial values are because of the loops

	/*
	//This won't work hardcoded, there are more than one [] group in input apparently lol
	string before = ip.substr(0, ip.find('['));
	string middle = ip.substr(ip.find('[') + 1, ip.find(']') - ip.find('[') - 1);
	string after = ip.substr(ip.find(']') + 1);

	abbaOut = hasAbba(before) || hasAbba(after);
	noAbbaIn = !hasAbba(middle);
	*/


	//Non hardcoded
	//Note: the getting of outer and inner probably could be done all at once and much more efficiently, but my head hurts and I'm not good with substrings lol

	vector<string> outer, inner;

	unsigned int pos = 0;

	//Getting outer and inner
	//Outer is the stuff outside of '[' and ']'
	//So, from 0 to the first '[' and from ']' to '[' until there are none, then being from ']' until the end

	//Inner is the stuff between '[' and ']', exclusively

	//The flag to switch between pushing to outer or to inner
	bool pushingToOuter = true;
	//For holding positions for the substr (for [ and ])
	int openPos = 0, closePos = -1; //close starts at -1 because of first substr for outer

	for (unsigned int i = 0; i < ip.length(); i++) {
		if (pushingToOuter) {
			if (ip[i] == '[') {
				openPos = i;
				outer.push_back(ip.substr(closePos + 1, openPos - closePos - 1));
				pushingToOuter = false;
			}
		}
		else {
			if (ip[i] == ']') {
				closePos = i;
				inner.push_back(ip.substr(openPos + 1, closePos - openPos - 1));
				pushingToOuter = true;
			}

		}
	}

	//Last outer isn't found in this for loop, because it is until the end
	outer.push_back(ip.substr(closePos + 1)); //From the last ']' until the end
	
	//Debug vector prints
	/*
	cout << "Outer: " << endl;
	Utilities::printVector(outer);

	cout << "\nInner: \n";
	Utilities::printVector(inner);
	*/
	
	//The termination condition has the extra && so that when a true is found the loop is exited, because nothing more needs to be checked
	//(The abbas in the outside are ORs, because there only needs to be one in total
	for (unsigned int i = 0; i < outer.size() && !abbaOut; ++i) {
		//This would be equivalent without requiring use of the && in the condition above
		/*
		if(hasAbba(outer[i]){
		abbaOut = true;
		break;
		}
		*/
		abbaOut |= hasAbba(outer[i]);
	}

	//Same idea as above but since there can be no abbas inside, the bool value is obtained through &=
	//(Sort of the negation of ||, which is &&)
	for (unsigned int i = 0; i < inner.size() && noAbbaIn; ++i) {
		noAbbaIn &= !hasAbba(inner[i]);
	}

	return abbaOut && noAbbaIn;
}

bool hasAbba(string str){
	//The check will be made by finding a sequence of 2 consecutive and equal characters,
	//then checking if the 2 characters around them are the same as well (and different from the middle ones)
	//This works because the minimum to be abba are 4 characters, and we only need to find one, not a certain number or size
	//Props to my dad for the idea
	
	//Starting at 1 because there are no outer chars to the left if 0,1 is a pair
	//The limit is reduced due to the condition in the if
	for(unsigned int i = 1; i < str.size() - 2; ++i){
		//If the two characters at i and i+1 are the same,
		//and the outer ones are also equal and different from the inner ones, the string has abba
		if (str[i] == str[i+1] && str[i-1] == str[i+2] && str[i+1] != str[i+2])
			return true;
	}
	
	return false;
}

bool checkSSL(string ip){

	//outer and inner getting is taken from TLS check since it is the same
	vector<string> outer, inner;

	unsigned int pos = 0;

	//Getting outer and inner
	//Outer is the stuff outside of '[' and ']'
	//So, from 0 to the first '[' and from ']' to '[' until there are none, then being from ']' until the end

	//Inner is the stuff between '[' and ']', exclusively

	//The flag to switch between pushing to outer or to inner
	bool pushingToOuter = true;
	//For holding positions for the substr (for [ and ])
	int openPos = 0, closePos = -1; //close starts at -1 because of first substr for outer

	for (unsigned int i = 0; i < ip.length(); i++) {
		if (pushingToOuter) {
			if (ip[i] == '[') {
				openPos = i;
				outer.push_back(ip.substr(closePos + 1, openPos - closePos - 1));
				pushingToOuter = false;
			}
		}
		else {
			if (ip[i] == ']') {
				closePos = i;
				inner.push_back(ip.substr(openPos + 1, closePos - openPos - 1));
				pushingToOuter = true;
			}

		}
	}

	//Last outer isn't found in this for loop, because it is until the end
	outer.push_back(ip.substr(closePos + 1)); //From the last ']' until the end
	
	//From now on it is different
	
	//Getting the ABAs from the outer sequence
	auto ABAs = getABAs(outer);
	
	return hasBAB(inner, ABAs);
	
}

//Used to find all the ABAs in a string - returns a pair of outerchar,innerchar (first second first outside [], second first second inside [])
vector<pair<char,char>> getABAs(const string &str){
	vector<pair<char,char>> output;
	
	for(unsigned int i = 1; i < str.size() - 1; ++i){
		//The middle one has to be different otherwise it would be AAA
		if(str[i-1] == str[i+1] && str[i] != str[i+1]){
			//Note to self, emplace uses no {}, inserts and such do, or use std::make_pair
			output.emplace_back(str[i-1], str[i]);
		}
	}
	
	return output;
}

//Used to find all the ABAs in a vector of strings
vector<pair<char,char>> getABAs(const vector<string> &outers){
	vector<pair<char,char>> output;
	vector<pair<char,char>> temptoinsert;
	
	for(const auto &outer : outers){
		temptoinsert = getABAs(outer);
		output.insert(output.end(), temptoinsert.begin(), temptoinsert.end());
	}
	
	return output;
}

bool hasBAB(const vector<string> &inners, const vector<pair<char,char>> &ABAs){
	//Go through each of the inside brackets stuff to check for a respective BAB to the ABA
	//If there is no need to check the others and return true straight away
	for(const auto &inner : inners){
		if(hasBAB(inner, ABAs))
			return true;
	}
	
	return false;
}

bool hasBAB(const string &inner, const vector<pair<char,char>> &ABAs){
	//Checking for a respective BAB for each of the ABAs in this inner
	for(const auto &ABA : ABAs){
		for(unsigned int i = 1; i < inner.size() - 1; ++i){
		//If the two characters at i-1 and i+1 are equal to ABA.second (B),
		//and the one at i is equal to ABA.first (A), the string has BAB
		if (inner[i-1] == ABA.second && inner[i+1] == ABA.second && inner[i] == ABA.first)
			return true;
		}
	}
	
	//If have gone through all ABAs and no return true, then it has no respective BAB
	return false;
}
