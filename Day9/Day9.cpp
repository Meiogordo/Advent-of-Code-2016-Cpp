#include <iostream>
#include <vector>
#include <string>

#include "Utils/Utilities.h"

using namespace std;


//Protos
void decompress(const string &input, string &output);
pair<int,int> getAxB(const string &insidebrackets);

int main() {
	
	vector<string> text = Utilities::ReadFile("Day9/Input.txt");
	//vector<string> text = {"X(8x2)(3x3)ABCY"}; //Manual for debugging
	
	string temp; // To hold the temporary decoded strings if they come in different lines 
	
	long unsigned int finalLength = 0;
	
	for(auto const &line : text){
		decompress(line, temp);
		finalLength += temp.size();
		//cout << "debug: " << temp << endl; //Don't forget to remove for final output or program might freeze lol
	}
	
	cout << "The final decompressed size of " << text.size() << " lines is " << finalLength << endl;
	
	return 0;
}

void decompress(const string &input, string &output){

	//In order to prevent redeclaration	
	string copystring;
	
	for (unsigned int i = 0; i < input.size(); ++i){
		if(input[i] == ' ') //ignoring whitespace
			continue;
		if(input[i] == '('){
			//decompressing here
			
			//getting the AxB to send to function
			//since at i is the '(', then the next ')' is the matching one
			
			unsigned int nextClose = input.find(')',i);//pos of the next closing parentheses
			
			auto AxB = getAxB(input.substr(i+1, nextClose - (i+1)));
			
			//Generating copystring
			copystring = input.substr(nextClose + 1, AxB.first); //Copy from the closing parentheses onwards for A characters
			
			//Copying decompressed into output
			//B is the number of times to be copied, copystring is the string to be copied
			for(unsigned int j = 0; j < AxB.second; ++j){
				output += copystring;
			}
			
			//Don't forget to move forward A times (minus 1 since the next iteration does ++ automatically) to ignore potential repeated decompressions (really A+5 because we need to skip the (AxB) thing AND the chars pointed at by A)
			//Something like
			i += AxB.first + 5 - 1;
		}else{
			//if not space or brackets, just copy the letter
			output.push_back(input[i]);
		}
	}
	
}

//Returns a pair in which A is the first and B the second
pair<int,int> getAxB(const string &insidebrackets){
	pair<int,int> output;
	
	output.first = stoi(insidebrackets.substr(0,insidebrackets.find_first_of('x')));
	output.second = stoi(insidebrackets.substr(insidebrackets.find_first_of('x') + 1));
	
	return output;
}
