#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseIt : public ParseDef
{
protected:
	Noun& n;
public:
	ParseIt(Noun& n) : ParseDef("It"), n(n) {}

	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
	
};
