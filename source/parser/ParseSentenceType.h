#pragma once
#include <string>
#include "../Language.h"
#include "ParseDef.h"

class ParseSentenceType : public ParseDef
{
protected:
	void setInt(std::string tag, int value, const ParserIO& io, Language& lang);
	void setBool(std::string tag, bool value, const ParserIO& io, Language& lang);
	void setString(std::string tag, std::string value, const ParserIO& io, Language& lang);
public:
	ParseSentenceType() : ParseDef("Sentence-Type") {}

	bool match(std::string name);
	void parse(ParserIO& io, Language& lang);
	
};
