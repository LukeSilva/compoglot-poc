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
	void parseArgs(ParserIO& io);
	
	virtual void setInt(std::string tag, int value);
	virtual void setBool(std::string tag, bool value);
	virtual void setString(std::string tag, std::string value);
public:
	ParseDef() : ParseElement("Definition") {}

	virtual bool match(std::string name);
	virtual void parse(ParserIO& io, Language& lang);
	
};
