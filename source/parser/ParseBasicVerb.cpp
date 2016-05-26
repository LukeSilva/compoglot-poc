#include <string>
#include "ParseException.h"
#include "ParseBasicVerb.h"

bool ParseBasicVerb::match(std::string name)
{
	VerbNum = BaseVerbNum;

	if (name=="Verb")
		return true;
	else if (name=="v1")
	{
		VerbNum = 0;
		return true;
	}
	else if (name=="v2")
	{
		VerbNum = 1;
		return true;
	}
	else if (name=="v3")
	{
		VerbNum = 2;
		return true;
	}
	return false;
}

void ParseBasicVerb::parse(ParserIO& io, Language& lang)
{
	beginParse(io);

	if (VerbNum == 0)
		lang.Verb1 = parseInt(io);
	else if (VerbNum == 1)
		lang.Verb2 = parseInt(io);
	else if (VerbNum == 2)
		lang.Verb3 = parseInt(io);
	else
		throw ParseException(std::string("Unknown VerbNum: ") + std::to_string(VerbNum) + ", while parsing " + name,io.getInput(),io.getCurPos());
	endParse(io);
}
