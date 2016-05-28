#include "ParseException.h"
#include "ParseIt.h"


bool ParseIt::match(std::string name)
{
	if (name == "it" || name == "It")
		return true;

	return false;
}

void ParseIt::parse(ParserIO& io, Language& lang)
{
	beginParse(io);

	Noun* itNoun = lang.getIt(parseInt(io));
	n = *itNoun;
	delete itNoun;

	endParse(io);
}
