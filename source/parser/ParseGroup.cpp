#include "ParseException.h"
#include "ParseGroup.h"

void ParseGroup::addElement(ParseElement* newElement)
{
	elements.push_back(newElement);
}

ParseGroup::~ParseGroup()
{
	for (std::vector<ParseElement*>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		delete *it;
	}
}

bool ParseGroup::match(std::string name)
{
	return true;
}

void ParseGroup::parse(ParserIO& io, Language& lang)
{
	io.expect('{',std::string("beginning of ") + name);
	
	while (io.peek(name) != '}')
	{
		std::string elementName = io.getName(name);
		bool found = false;
		for (std::vector<ParseElement*>::iterator it = elements.begin(); it != elements.end(); ++it)
		{
			if ((*it)->match(elementName))
			{
				(*it)->parse(io,lang);
				found = true;
				break;
			}
		}

		if (!found && elementName != "")
			throw ParseException(std::string("Unknown element ") + elementName + ", while parsing " + name,io.getInput(),io.getCurPos());
		else if (!found && !std::isalnum(io.peek(name)))
			throw ParseException(std::string("Unexpected character '") + io.peek(name) + "', while parsing " + name,io.getInput(),io.getCurPos());
		
		io.skipWhitespace(name);
	}

	io.expect('}',std::string("end of ") + name);
	
	
}
