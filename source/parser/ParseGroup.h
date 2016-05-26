#pragma once
#include <string>
#include <vector>
#include "../Language.h"
#include "ParseElement.h"

class ParseGroup : public ParseElement
{
private:
	std::vector<ParseElement*> elements;
protected:
	ParseGroup(std::string name) : ParseElement(name + "(Group)") {}
public:
	// For testing this is public.
	void addElement(ParseElement* newElement);

	ParseGroup() : ParseElement("Group") {}
	~ParseGroup();

	bool match(std::string name);
	virtual void parse(ParserIO& io, Language& lang);
	
};
