#include "ParseException.h"
#include "ParseNoun.h"

#include "ParseNounGroup.h"


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
	else
		throw ParseException(std::string("Invalid int-tag \"") + tag + "\", while parsing " + name,io.getInput(),io.getCurPos());
}

void ParseNoun::setBool(const ParserIO& io, Language& lang,std::string tag, bool value)
{
	if (tag == "reflex" || tag == "Reflexive")
	{
		n.IsReflexive = value;
	}
	else
		throw ParseException(std::string("Invalid bool-tag \"") + tag + "\", while parsing " + name,io.getInput(),io.getCurPos());
}

void ParseNoun::setGroup(ParserIO& io, Language& lang,std::string tag)
{
	if (tag == "genitive" || tag == "GenitiveNoun")
	{
		Noun * genitive = new Noun();
		ParseNounGroup g(*genitive);
		g.parse(io,lang);

		n.GenitiveNoun = genitive;
		n.ShouldUseGenitive = true;
	}
	else
		throw ParseException(std::string("Invalid bool-tag \"") + tag + "\", while parsing " + name,io.getInput(),io.getCurPos());
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
