#pragma once
#include <string>
#include "../Language.h"
#include "parserIO.h"
#include "parseException.h"

class Parser
{
public:
	void parseExt(std::string cmd,Language* lang);
	std::string parse(std::string langid, std::string cmd);
};
