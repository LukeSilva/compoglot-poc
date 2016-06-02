#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseProperties : public ParseDef
{
protected:
	void setInt(const ParserIO& io, Language& lang,std::string tag, int value);
	void setBool(const ParserIO& io, Language& lang,std::string tag, bool value);
	bool IsSubject;
	int ObjectID;
	Noun* n;
public:
	ParseProperties() : ParseDef("Properties"), IsSubject(true), ObjectID(0), n(NULL) {}
	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
};
