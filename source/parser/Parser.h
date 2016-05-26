#pragma once
#include <string>
#include "../Language.h"
#include "ParserIO.h"
#include "ParseException.h"
#include "ParseGroup.h"

class Parser : public ParseGroup
{
private:
	
public:
	Parser();
	void parse(ParserIO& io, Language& lang) {ParseGroup::parse(io,lang);};
	void parseExt(std::string cmd,Language* lang, int VerbNum);
	std::string parse(std::string langid, std::string cmd);
};
