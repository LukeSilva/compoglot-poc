#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

#include "parserIO.h"

class parseException
{
	int pos;
	std::string error;
	std::string input;

public: 
	parseException(std::string error, std::string input, int pos) : pos(pos), error(error), input(input) {}

	// friend allows access to this exceptions private members
	friend std::ostream& operator<<(std::ostream& os, const parseException& pe);
};

std::ostream& operator<<(std::ostream& os, const parseException& pe);
