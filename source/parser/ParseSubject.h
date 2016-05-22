#pragma once
#include <string>
#include "../Language.h"
#include "ParseElement.h"

class ParseSubject : public ParseElement
{
public:
	ParseSubject() : ParseElement("Subject") {}

	virtual bool match(std::string name);
	virtual void parse(ParserIO& io, Language& lang);
	
};
