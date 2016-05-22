#pragma once
#include <string>
#include "../Language.h"
#include "ParseElement.h"

class ParseList : public ParseElement
{
public:
	ParseList() : ParseElement("List") {}

	virtual bool match(std::string name);
	virtual void parse(ParserIO& io, Language& lang);
	
};
