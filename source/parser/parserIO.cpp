#include <stdexcept>
#include <iostream>
#include "parseException.h"
#include "parserIO.h"

void parserIO::expect(char character)
{
	try
	{
		if (input.at(curPos)!=character)
		{
			throw parseException(std::string("Unexpected character '") + input.at(curPos) + "', expected '" + character + "'", input, curPos);
		}
	}
	catch (const std::out_of_range& oor)
	{
		throw parseException(std::string("Unexpected end of input, expected '") + character + "'",input,curPos);
	}
}

char parserIO::peek()
{
	try
	{
		return input.at(curPos);
	}
	catch (const std::out_of_range& oor)
	{
		throw parseException("Unexpected end of input",input,curPos);
	}
}
