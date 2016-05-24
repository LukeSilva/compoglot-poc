#pragma once
#include <string>
#include "../Language.h"
#include "ParseList.h"

class ParseSubject : public ParseList
{
public:
	ParseSubject() : ParseList("Subject") {}

	ParseGroup* getGroup();

	bool match(std::string name);
	
};
