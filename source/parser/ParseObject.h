#pragma once
#include <string>
#include "../Language.h"
#include "ParseGroup.h"


class ParseObject: public ParseGroup
{
public:
	ParseObject();
	bool match(std::string tag);
};
