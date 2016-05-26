#include <string>
#include "ParseException.h"
#include "ParseExtVerb.h"

bool ParseExtVerb::match(std::string name)
{
	if (name=="Verb1")
	{
		VerbNum = 0;
		return true;
	}
	else if (name == "Verb2")
	{
		VerbNum = 1;
		return true;
	}
	else if (name == "Verb3")
	{
		VerbNum = 2;
		return true;
	}
	return false;
}

void ParseExtVerb::parse(ParserIO& io, Language& lang)
{
	beginParse(io);

	if (VerbNum == 0)
		lang.ExtVerb1 = parseInt(io);
	else if (VerbNum == 1)
		lang.ExtVerb2 = parseInt(io);
	else if (VerbNum == 2)
		lang.ExtVerb3 = parseInt(io);
	else
		throw ParseException(std::string("Unknown VerbNum: ") + std::to_string(VerbNum) + ", while parsing " + name,io.getInput(),io.getCurPos());
	endParse(io);
}
