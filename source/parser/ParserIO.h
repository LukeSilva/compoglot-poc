#pragma once
#include <string>

class ParserIO
{
	int curPos;
	std::string input;

public:
	ParserIO(std::string in) : curPos(0), input(in) {};
	ParserIO() : curPos(0), input("") {};
	
	std::string getInput();
	int getCurPos();

	char peek(std::string state);		// Returns the current character, without moving forward
	char get(std::string state); 		// Gets the current character, and moves forward by one

	void skipWhitespace(std::string state);
	void expect(char expectedChar,std::string state);


	std::string getName(std::string state); // [a-zA-Z0-9]*
	std::string getString(std::string state); // \".*\"
	int  getInt(std::string state);  	// -[0-9]* | [0-9]*
	bool getBool(std::string state); 	// "true","false","T","F"
};
