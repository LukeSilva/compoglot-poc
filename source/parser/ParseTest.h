#pragma once
#include <string>
#include "../Language.h"
#include "ParseElement.h"

class ParseTestElement : public ParseElement
{
public:
	ParseTestElement() : ParseElement("Test") {}

	virtual bool match(std::string name);
	virtual void parse(ParserIO& io, Language& lang);
	
};
