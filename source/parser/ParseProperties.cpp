#include "ParseException.h"
#include "ParseProperties.h"

void ParseProperties::setInt(const ParserIO& io, Language& lang,std::string tag, int value)
{
	if (tag == "prepos" || tag == "Preposition")
	{
		for (int i = 0; i < 16; ++i)
			n[i].PreposNum = value;	
	}
	else if (tag == "article" || tag == "Article")
	{
		for (int i = 0; i < 16; ++i)
			n[i].ArticleType = value;
	}
	else if (tag == "data" || tag == "Data")
	{
		for (int i = 0; i < 16; ++i)
			n[i].Data = value;
	}
	else
		throw ParseException(std::string("Invalid int-tag \"") + tag + "\", while parsing " + name,io.getInput(),io.getCurPos());
}

void ParseProperties::setBool(const ParserIO& io, Language& lang,std::string tag, bool value)
{
	if (tag == "reflex" || tag == "Reflexive")
	{
		for (int i = 0; i < 16; ++i)
			n[i].IsReflexive = value;
	}
	else 
		throw ParseException(std::string("Invalid bool-tag \"") + tag + "\", while parsing " + name,io.getInput(),io.getCurPos());

}

bool ParseProperties::match(std::string name)
{
	if (name == "sprop" || name == "SubjectProperties")
	{
		IsSubject = true;
		return true;
	}
	else if (name == "oprop" || name == "ObjectProperties")
	{
		IsSubject = false;
		return true;
	}
	return false;
}

void ParseProperties::parse(ParserIO& io,Language& lang)
{
	beginParse(io);

	if (!IsSubject)
	{
		ObjectID = parseInt(io) - 1;
		if (ObjectID < 0 || ObjectID > 7)
			throw ParseException("Invalid ObjectID, must be between 1 and 8, while parsing Properties",io.getInput(),io.getCurPos());
		n = lang.Objects[ObjectID];
	}
	else
		n = lang.Subjects;

	parseArgs(io,lang);

	endParse(io);
}
