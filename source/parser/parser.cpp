#include <iostream>
#include "parser.h"

void Parser::parseExt(std::string cmd, Language* lang)
{
}

std::string Parser::parse(std::string langid, std::string cmd)
{
	try
	{
		parserIO p(cmd);
		p.expect('{');


	}
	catch (parseException& pe)
	{
		std::cerr << pe << std::endl;
		return "";
	}
	return "";
}

