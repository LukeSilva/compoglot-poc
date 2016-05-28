#include "ParseException.h"
#include "ParseAdjective.h"


bool ParseAdjective::match(std::string name)
{
	if (name == "adj" || name == "Adjective")
		return true;

	return false;
}

void ParseAdjective::parse(ParserIO& io, Language& lang)
{
	beginParse(io);
	n.addAdjective(parseInt(io));
	endParse(io);
}
