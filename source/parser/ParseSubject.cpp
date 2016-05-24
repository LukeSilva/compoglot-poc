#include <iostream>
#include "ParseSubject.h"
#include "ParseTest.h"

ParseGroup* ParseSubject::getGroup()
{
	ParseGroup* g = new ParseGroup();
	g->addElement(new ParseTestElement());
	return g;
}

bool ParseSubject::match(std::string name)
{
	if (name == "sub")
		return true;
	return false;
}


