#pragma once
#include <string>
#include "../Language.h"
#include "ParserIO.h"

class ParseElement
{
protected:
	std::string name;
	ParseElement(std::string name) : name(name) {}
public:
	ParseElement() : name("Element") {}
	virtual ~ParseElement() {}
	
	// Returns true if the name matches the element type
	// Always returns false in this prototype
	virtual bool match(std::string name);
	// Called to parse the element
	virtual void parse(ParserIO& io, Language& lang);
};
