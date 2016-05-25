#include <iostream>
#include <cctype>
#include "ParseDef.h"

bool ParseDef::match(std::string name)
{
	if (name == "def")
		return true;
	return false;
}

void ParseDef::beginParse(ParserIO& io)
{
	io.expect('(',name);
	needComma = false;
}

void ParseDef::endParse(ParserIO& io)
{
	io.expect(')',name);
}

void ParseDef::setInt(const ParserIO& io, Language& lang,std::string tag, int value)
{
	std::cout << "ParserIntArg " << tag << " = " << value << std::endl;
}

void ParseDef::setBool(const ParserIO& io, Language& lang,std::string tag, bool value)
{
	std::cout << "ParserBoolArg " << tag << " = " << value << std::endl;
}

void ParseDef::setString(const ParserIO& io, Language& lang,std::string tag, std::string value)
{
	std::cout << "ParserStringArg " << tag << " = " << value << std::endl;
}

int ParseDef::parseInt(ParserIO& io)
{
	io.skipWhitespace(name);

	if (needComma)
	{
		io.expect(',',name);
		io.skipWhitespace(name);
	}

	int returnInt = io.getInt(name);
	needComma = true;
	return returnInt;
}

bool ParseDef::parseBool(ParserIO& io)
{
	io.skipWhitespace(name);

	if (needComma)
	{
		io.expect(',',name);
		io.skipWhitespace(name);
	}

	int returnBool = io.getBool(name);
	needComma = true;
	return returnBool;
}

void ParseDef::parseArgs(ParserIO& io, Language& lang)
{
	io.skipWhitespace(name);
	
	while (io.peek(name) != ')')
	{
		if (needComma)
		{
			io.expect(',',name);
			io.skipWhitespace(name);
		}
		
		std::string tag = io.getName(name);

		io.skipWhitespace(name);
		io.expect('=',name);
		io.skipWhitespace(name);

		if (std::isdigit(io.peek(name)))
			setInt(io,lang,tag,io.getInt(name));
		else if (io.peek(name) == '"' || io.peek(name)=='\'')
			setString(io,lang,tag,io.getString(name));
		else
			setBool(io,lang,tag,io.getBool(name));

		io.skipWhitespace(name);

		needComma = true;
	}
}

void ParseDef::parse(ParserIO& io, Language& lang)
{
	std::cout << "Test Definition" << std::endl;
	beginParse(io);
	std::cout << "INT:  " << parseInt(io) << std::endl;
	std::cout << "BOOL: " << parseBool(io) << std::endl;

	parseArgs(io,lang);		

	endParse(io);
}
