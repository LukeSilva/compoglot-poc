#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseNoun : public ParseDef
{
protected:
	Noun& n;

	void setInt(const ParserIO& io, Language& lang,std::string tag, int value);
	void setBool(const ParserIO& io, Language& lang,std::string tag, bool value);
	void setGroup(ParserIO& io, Language& lang,std::string tag);
public:
	ParseNoun(Noun& n) : ParseDef("Noun"), n(n) {}

	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
	
};
