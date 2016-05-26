#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseBasicVerb : public ParseDef
{
private:
	int BaseVerbNum;
	int VerbNum;
public:
	ParseBasicVerb(int VerbNum) : ParseDef("BasicVerb"), BaseVerbNum(VerbNum), VerbNum(VerbNum){}

	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
	
};
