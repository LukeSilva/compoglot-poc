#include <iostream>
#include <sstream>
#include "ParseObjList.h"

#include "ParseNounGroup.h"

ParseGroup* ParseObjList::getGroup(Language& lang)
{

	lang.NumFilledObjects[id] += 1;

	return new ParseNounGroup(lang.Objects[id][lang.NumFilledObjects[id]]);
}

bool ParseObjList::match(std::string name)
{
	std::ostringstream ss;
	ss << (id+1);

	if (name == ss.str())
		return true;
	return false;
}


