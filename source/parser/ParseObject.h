#pragma once
#include <string>
#include "../Language.h"
#include "ParseGroup.h"


class ParseObject: public ParseGroup
{
public:
	ParseObject() : ParseGroup("GroupObj");
	bool match(std::string tag);
};
