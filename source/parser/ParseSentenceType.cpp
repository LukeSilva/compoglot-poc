#include "ParseException.h"
#include "ParseSentenceType.h"

void ParseSentenceType::setBool(const ParserIO& io, Language& lang, std::string tag, bool value)
{
	if (tag=="neg" || tag == "Negate")
	{
		lang.Negate = value;
	}
	else if (tag=="question")
	{
		lang.Question = value ? 1 : 0;
	}
	else
		throw ParseException(std::string("Invalid bool-tag \"") + tag + "\", while parsing " + name,io.getInput(),io.getCurPos());
}

void ParseSentenceType::setInt(const ParserIO& io, Language& lang, std::string tag, int value)
{
	if (tag=="punc" || tag=="Punctuation")
	{
		lang.Punctuation = value;
	}
	else
		throw ParseException(std::string("Invalid int-tag \"") + tag + "\", while parsing " + name,io.getInput(),io.getCurPos());
}

bool ParseSentenceType::match(std::string name)
{
	if (name == "st" || name == "SentenceType")
		return true;
	return false;
}

void ParseSentenceType::parse(ParserIO& io, Language& lang)
{
	beginParse(io);

	lang.st = parseInt(io);
	
	parseArgs(io,lang);

	endParse(io);
}
