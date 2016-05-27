#include "ParseException.h"
#include "ParseNoun.h"


bool ParseNoun::match(std::string name)
{
	if (name == "n" || name == "Noun")
		return true;

	return false;
}

void ParseNoun::parse(ParserIO& io, Language& lang)
{
	beginParse(io);
	n.ID = parseInt(io);
	n.ArticleType = parseInt(io);
	n.IsPlural = parseBool(io);
	endParse(io);
}
