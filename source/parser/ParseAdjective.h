#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseAdjective : public ParseDef
{
protected:
	Noun& n;
public:
	ParseAdjective(Noun& n) : ParseDef("Adjective"), n(n) {}

	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
	
};
