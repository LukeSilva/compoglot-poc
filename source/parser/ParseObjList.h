#pragma once
#include <string>
#include "../Language.h"
#include "ParseList.h"

class ParseObjList : public ParseList
{
private:
	int id;
public:
	ParseObjList(int id) : ParseList("ObjectList"), id(id) {}

	ParseGroup* getGroup(Language& lang);

	bool match(std::string name);
	
};
