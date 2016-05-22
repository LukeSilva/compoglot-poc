#pragma once
#include <string>

class parserIO
{
	int curPos;
	std::string input;

	void skipWhitespace();
public:
	parserIO(std::string in) : curPos(0), input(in) {};
	parserIO() : curPos(0), input("") {};

	void expect(char expectedChar);
	char peek();    // currentCharacter
	std::string getName(); // [a-zA-Z0-9]*
	int  getInt();  // -[0-9]* | [0-9]*
	bool getBool(); // "true","false","T","F"
};
