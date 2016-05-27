#include "ParseList.h"

ParseGroup* ParseList::getGroup(Language& lang)
{
	return new ParseGroup();
}

bool ParseList::match(std::string name)
{
	return true;
}

void ParseList::parse(ParserIO& io, Language& lang)
{
	io.expect('[',name);
	io.skipWhitespace(name);

	ParseGroup* g = getGroup(lang);
	g->parse(io,lang);
	delete g;

	while (io.peek(name)==',')
	{
		io.expect(',',name);
		io.skipWhitespace(name);

		g = getGroup(lang);
		g->parse(io,lang);
		delete g;

		io.skipWhitespace(name);
	}
	
	io.expect(']',name);
}
