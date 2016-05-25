#pragma once
#include <string>
#include "../Language.h"
#include "ParseElement.h"

class ParseDef : public ParseElement
{
private:
	bool needComma;
protected:
	void beginParse(ParserIO& io);
	void endParse(ParserIO& io);

	int parseInt(ParserIO& io);
	bool parseBool(ParserIO& io);
	void parseArgs(ParserIO& io, Language& lang);
	
	virtual void setInt(std::string tag, int value, const ParserIO& io, Language& lang);
	virtual void setBool(std::string tag, bool value, const ParserIO& io, Language& lang);
	virtual void setString(std::string tag, std::string value, const ParserIO& io, Language& lang);

	ParseDef(std::string name) : ParseElement(name + " (Def)") {};
public:
	ParseDef() : ParseElement("Definition") {}

	virtual bool match(std::string name);
	virtual void parse(ParserIO& io, Language& lang);
	
};
