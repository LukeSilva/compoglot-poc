#include <iostream>
#include "Parser.h"

void Parser::parseExt(std::string cmd, Language* lang)
{
}

std::string Parser::parse(std::string langid, std::string cmd)
{
	try
	{
		ParserIO p(cmd);
		p.skipWhitespace("beginning of input");
		p.expect('{',"beginning of input");

		std::cout << p.getInt("initial int");
		
		return ":D";
	}
	catch (ParseException& pe)
	{
		std::cerr << pe << std::endl;
		return "";
	}

}

