#pragma once
#include <string>
#include "../Language.h"
#include "ParserIO.h"
#include "ParseException.h"

class Parser
{
public:
	void parseExt(std::string cmd,Language* lang);
	std::string parse(std::string langid, std::string cmd);
};
