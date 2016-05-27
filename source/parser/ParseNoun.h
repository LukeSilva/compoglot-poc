#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseNoun : public ParseDef
{
protected:
	Noun& n;
public:
	ParseNoun(Noun& n) : ParseDef("Noun"), n(n) {}

	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
	
};
