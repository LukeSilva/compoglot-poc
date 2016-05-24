#include <iostream>
#include "ParseTest.h"

bool ParseTestElement::match(std::string name)
{
	if (name == "test")
		return true;
	return false;
}

void ParseTestElement::parse(ParserIO& io, Language& lang)
{
	io.expect('(',name);
	io.expect(')',name);
	std::cout << "Test Element" << std::endl;
}
