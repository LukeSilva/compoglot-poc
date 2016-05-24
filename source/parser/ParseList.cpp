#include "ParseList.h"

ParseGroup* ParseList::getGroup()
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

	ParseGroup* g = getGroup();
	g->parse(io,lang);
	delete g;

	while (io.peek(name)==',')
	{
		io.expect(',',name);
		io.skipWhitespace(name);

		g = getGroup();
		g->parse(io,lang);
		delete g;

		io.skipWhitespace(name);
	}
	
	io.expect(']',name);
}
