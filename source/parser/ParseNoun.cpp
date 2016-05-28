#include "ParseException.h"
#include "ParseNoun.h"


void ParseNoun::setInt(const ParserIO& io, Language& lang,std::string tag, int value)
{
	if (tag == "num" || tag == "Numeral")
	{
		n.Numeral = value;
		if (value > 1 || value < -1)
			n.IsPlural = true;
	}
	else if (tag == "prepos" || tag == "Preposition")
		n.PreposNum = value;
}

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

	parseArgs(io,lang);

	endParse(io);
}
