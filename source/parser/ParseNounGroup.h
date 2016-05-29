#pragma once
#include <string>
#include "../Language.h"
#include "ParseGroup.h"

class ParseNounGroup : public ParseGroup
{
public:
	ParseNounGroup(Noun & n);
};
