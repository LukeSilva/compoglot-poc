#include <iostream>
#include "ParseSubject.h"

bool ParseSubject::match(std::string name)
{
	if (name == "sub")
		return true;
	return false;
}

void ParseSubject::parse(ParserIO& io, Language& lang)
{
	std::cout << "SUBJECT PARSE :D" << std::endl;
	io.expect(';',name);
}
