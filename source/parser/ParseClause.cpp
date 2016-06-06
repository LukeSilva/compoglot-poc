#include "ParseClause.h"

#include "Parser.h"

bool ParseClause::match(std::string name)
{
	if (name == "clause" || name == "Clause")
	{
		return true;
	}
	return false;
}

void ParseClause::parse(ParserIO& io, Language& lang)
{
	beginParse(io);

	int Conjunction = parseInt(io);
	
	io.skipWhitespace(name);
	io.expect(',',name);
	io.skipWhitespace(name);
	
	std::shared_ptr<Language> clause = getLanguageFromStringID(lang.LangID);
	Parser p;
	p.parse(io,*clause);

	clause->IsClause = true;

	lang.Conjunction = Conjunction;
	lang.SubClause = clause;
	
	endParse(io);
}
