#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseExtVerb : public ParseDef
{
private:
	int VerbNum = 0;
public:
	ParseExtVerb() : ParseDef("ExtVerb") {}

	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
	
};
