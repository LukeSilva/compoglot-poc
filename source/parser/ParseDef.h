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
	
	virtual void setInt(const ParserIO& io, Language& lang,std::string tag, int value);
	virtual void setBool(const ParserIO& io, Language& lang,std::string tag, bool value);
	virtual void setString(const ParserIO& io, Language& lang,std::string tag, std::string value);

	ParseDef(std::string name) : ParseElement(name + " (Def)") {};
public:
	ParseDef() : ParseElement("Definition") {}

	virtual bool match(std::string name);
	virtual void parse(ParserIO& io, Language& lang);
	
};
