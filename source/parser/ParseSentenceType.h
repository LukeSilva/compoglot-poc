#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseSentenceType : public ParseDef
{
protected:
	void setInt(const ParserIO& io, Language& lang,std::string tag, int value);
	void setBool(const ParserIO& io, Language& lang,std::string tag, bool value);
	void setString(const ParserIO& io, Language& lang,std::string tag, std::string value);
public:
	ParseSentenceType() : ParseDef("Sentence-Type") {}

	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
	
};
