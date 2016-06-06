#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseClause : public ParseDef
{
public:
	ParseClause() : ParseDef("Clause") {}
	
	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
};
