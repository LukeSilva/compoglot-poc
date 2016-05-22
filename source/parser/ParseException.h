#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

#include "ParserIO.h"

class ParseException
{
	int pos;
	std::string error;
	std::string input;
	std::string state;

public: 
	ParseException(std::string error, std::string input, int pos) : pos(pos), error(error), input(input) {}

	// friend allows access to this exceptions private members
	friend std::ostream& operator<<(std::ostream& os, const ParseException& pe);
};

std::ostream& operator<<(std::ostream& os, const ParseException& pe);
