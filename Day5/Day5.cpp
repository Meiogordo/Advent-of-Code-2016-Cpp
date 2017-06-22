//Ugh.. MD5 hashing once again...
#include <iostream>
#include <vector>
#include <string>

#include "Utils/Utilities.h"
//For generating md5 hashes
#include "Utils/md5.h"

using namespace std;


//Protos
string generatePassword(string doorID);
string generatePasswordP2(string doorID);


int main() {
	
	//string inputID = "abc"; //For testing
	string inputID = "ojvtpuvg";
	
	//Part 1
	//cout << "The password for the given ID, " << inputID << " is " << generatePassword(inputID) << endl;
	//Part 2
	cout << "The password for the given ID, " << inputID << " is " << generatePasswordP2(inputID) << endl;
	
	return 0;
}

string generatePassword(string doorID){
	string password = "";
	string temphash;
	
	for(unsigned long long int i = 0; password.size() < 8; ++i){
		//Generating md5 hash of the doorID with the appended counter at the end
		temphash = md5(doorID + to_string(i));
		
		/*
		if (i % 737373 == 0)
		//Sanity checking while also trying to not force too many prints (apparently this was actually the biggest slowdown lol)
			cout << "Debug, i: " << i << endl;
		*/	
		
		//If the hash has five consecutive 0s at the begginning
		if(temphash.substr(0,5) == "00000"){
			//then, append the number after the 0s to the password
			password.push_back(temphash[5]); //Getting the character at the 6th position
			//Pretty sanity checks
			cout << "Debug, new letter found at position " << i << ", letter " << temphash[5];
			cout << "\nPassword is now " << password << endl;
		}
	}
	
	return password;
}

string generatePasswordP2(string doorID){
	string password = "________";
	string temphash;
	
	//Termination condition is not finding any occurrence of '_' in password. So we do it while we find, while .find returns != npos
	for(unsigned long long int i = 0; password.find('_') != string::npos ; ++i){
		//Generating md5 hash of the doorID with the appended counter at the end
		temphash = md5(doorID + to_string(i));	
		
		//If the hash has five consecutive 0s at the begginning
		if(temphash.substr(0,5) == "00000"){
			char position = temphash[5];
			//cout << "New letter found at i=" << i << ", letter " << temphash[6] << ", position " << temphash[5] << endl;
			//Checking if the position char is valid
			if (position >= '0' && position <= '7'){
				//Now, checking if the position is already taken
				if (password[position - '0'] == '_'){
					cout << "It fits! " << temphash[6] << " was at i=" << i << " and is now in password position " << position;
					password[position - '0'] = temphash[6];
					cout << "\nPassword is now: " << password << endl;
				} //else cout << "But the position was already taken..." << endl;
			} //else cout << "But the position was invalid... (Was " << temphash[5] << ")" << endl;
		}
	}
	
	return password;
}
