#include <iostream>
#include <vector>
#include <string>

#include "Utils/Utilities.h"

using namespace std;


//Protos
bool checkTLS(string ip);
bool hasAbba(string str);


int main() {
	
	//vector<string> text = Utilities::ReadFile("Day7/Input.txt");
	vector<string> text = {"abbbba[asdfgh]zxcvbn[schweg]ilovecats[iloveabba]thereisalsoabbaout"}; //Manual for debugging
	
	long unsigned int tlsCounter = 0;
	
	for(auto const &ip : text){
		tlsCounter += checkTLS(ip);
	}
	
	cout << "Out of " << text.size() << " IPv7 IPs, " << tlsCounter << " support TLS" << endl;
	
	return 0;
}

bool checkTLS(string ip){
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
	
	//Getting outer
	//Outer is the stuff outside of '[' and ']'
	//So, from 0 to the first '[' and from ']' to '[' until there are none, then being from ']' until the end
	
	//First done outside for ease of coding
	outer.push_back(ip.substr(0, ip.find('[') - 0));
	
	pos = ip.find(']');
	
	//While there is an '[' after the current ']'
	while(ip.find('[', pos) != string::npos){
		
		outer.push_back(ip.substr(pos + 1, ip.find('[', pos) - pos - 1));
		
		//Updating pos
		pos = ip.find(']', pos);	
	}
	
	//Final one is until the end of the string
	outer.push_back(ip.substr(pos + 1));
	
	pos = 0;
	
	//Getting inner
	//Inner is the stuff between '[' and ']', exclusively
	while(ip.find('[', pos) != string::npos){
		//Since the '[' was found, updating pos
		pos = ip.find('[', pos);
		//Getting substr and pushing it back
		inner.push_back(ip.substr(pos, ip.find(']', pos) - pos - 1));
	}
	
	cout << "Outer: " << endl;
	Utilities::printVector(outer);
	
	cout << "\nInner: \n";
	Utilities::printVector(inner);
	
	//The termination condition has the extra && so that when a true is found the loop is exited, because nothing more needs to be checked
	//(The abbas in the outside are ORs, because there only needs to be one in total
	for(unsigned int i = 0; i < outer.size() && !abbaOut; ++i){
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
	for(unsigned int i = 0; i < inner.size() && noAbbaIn; ++i){
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
