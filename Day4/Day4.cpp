//Note: part 2 causes weird encoding for some reason but partial searches still resulted in the right answer so that's fine by me

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "Utils/Utilities.h"

using namespace std;

//Protos
//Checks if room is real, returns 0 if it is not, returns sector if it is real
unsigned int roomStuff(string room);
//Used to generate checksum, to compare with the given checksum
string generateChecksum(const map<char, unsigned int> &letters);
//used to sort the vector of pairs
bool sortfunc(const pair<char, unsigned int> &p1, const pair<char, unsigned int> &p2);

//Self explanatory names, decrypting functions

string decryptName(string room);
char decryptChar(char crypted, int shift);


int main() {
	
	vector<string> text = Utilities::ReadFile("Day4/Input.txt");
	//vector<string> text = {"aaaaa-bbb-z-y-x-123[abxyz]"}; //Manual for debugging
	
	//Sums the sector numbers
	long unsigned int sectorcounter = 0;
	//Counts the number of rooms
	unsigned int roomcounter = 0;
	//Temp to avoid double calling roomStuff
	unsigned int temp = 0;
	
	for(auto const &room : text){
		temp = roomStuff(room);
		/*
		//Part 1
		sectorcounter += temp;
		roomcounter += (temp != 0);
		*/
		
		//Part 2
		if(temp != 0) //room is real
			cout << decryptName(room) << ", sector nr: " << temp << endl;
	}
	
	//Part 1
	//cout << "The sum of the sectors of " << roomcounter << " real rooms is " << sectorcounter << endl;
	
	return 0;
}

unsigned int roomStuff(string room){
	//Letters map to count number of ocurrences of the letters
	map<char, unsigned int> letters;
	
	//Getting checksum to compare
	string checksum = room.substr(room.find("[") + 1, room.find("]") - room.find("[") - 1);
	
	//Getting remainder letters in the string
	string rawletters = room.substr(0, room.find_last_of("-"));
	
	for(auto const &character : rawletters){
		if(character == '-')
			continue;
		++letters[character];
	}
	
	//Debug
	//cout << "Generated checksum: " << generateChecksum(letters) << "\tGiven checksum: " << checksum << endl;
	
	//Room is fake
	if(generateChecksum(letters) != checksum)
		return 0;
	
	//Room is real
	unsigned int sectornumber = stoi(room.substr(room.find_last_of("-") + 1, room.find("[") - room.find_last_of("-") - 1));
	return sectornumber;
}

string generateChecksum(const map<char, unsigned int> &letters){
	//Copying the map to a vector
	vector<pair<char, unsigned int>> lettersvec(letters.begin(), letters.end());
	
	string output;
	
	//sorting the vector in descending order using sortfunc
	sort(lettersvec.begin(), lettersvec.end(), sortfunc);
	
	//Because the sort already considers the alphabetic rule if the number of ocurrences is the same
	//We only need to get the first 5 letters out to generate the checksum
	for(unsigned int i = 0; i < 5; ++i){
		output.push_back(lettersvec[i].first);
	}

	return output;
}

bool sortfunc(const pair<char, unsigned int> &p1, const pair<char, unsigned int> &p2){
	if(p1.second == p2.second)
		return p1.first < p2.first;
	else
		return p1.second > p2.second;
}

string decryptName(string room){
	string output = "";
	
	string letters = room.substr(0, room.find_last_of("-"));
	unsigned int sectorID = stoi(room.substr(room.find_last_of("-") + 1, room.find("[") - room.find_last_of("-") - 1));
	
	for(auto const &letter : letters){
		if(letter == '-')
			output.push_back(' ');
		else
			output.push_back(decryptChar(letter, sectorID));
	}
	
	return output;
}

char decryptChar(char crypted, int shift){
	shift %= 26; //Reducing the shift to remove unnecessary looparounds
	crypted += shift;

	if (crypted > 'z') //Assuming all characters are lowercase
		crypted -= 26; //looped around so we subtract to put it back in the letter range

	return crypted;
}
