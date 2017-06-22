#!/bin/bash
#The script should be ran as ./createDay <DayNumber>, for example ./createDay 6

#Check if an argument was given
#Basically checking if the number of arguments is 0 ($# returns the number of arguments)
if [[ $# -eq 0 ]]
then
	echo
	echo "No arguments were supplied!"
	echo "Exiting!"
	exit 3 #exit on error=no arguments provided
fi

#Checking if the given argument is a number
if [[ -n ${1//[0-9]/} ]]
then #(Checking if the variable, evaluated in arithmetic context, is equal to itself)
	echo
	echo "Given argument is not a number!"
	echo "Exiting!"
	exit 4 #exit on error=argument not a number
fi

#Checking if the cpp file for the given day already exists
if [[ -s Day$1/Day$1.cpp ]]
then
	echo
	echo "The cpp file for that day already exists and is not empty!"
	echo "The new cpp was not created!"
	exit 5 #exit on error=cpp already exists
fi

if [[ ! -f Template/DayTemplate.cpp ]]
then
	echo
	echo "The template cpp file does not exist!"
	echo "The new cpp was not created!"
	exit 6 #exit on error=template does not exist
fi


#Making the directory for the day
mkdir Day$1
#Copying the template cpp to make the new cpp
cp Template/DayTemplate.cpp Day$1/Day$1.cpp

#Done
echo "Done."
