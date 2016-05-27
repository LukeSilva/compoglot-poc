#pragma once
#include <string>
#include "../Language.h"
#include "ParseList.h"

class ParseSubject : public ParseList
{
public:
	ParseSubject() : ParseList("Subject") {}

	ParseGroup* getGroup(Language& lang);

	bool match(std::string name);
	
};
