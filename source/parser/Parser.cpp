#include <iostream>
#include "Parser.h"

#include "ParseGroup.h"
#include "ParseSubject.h"
#include "ParseDef.h"

void Parser::parseExt(std::string cmd, Language* lang)
{
}

std::string Parser::parse(std::string langid, std::string cmd)
{
	try
	{
		ParserIO p(cmd);
		p.skipWhitespace("beginning of input");
		
		ParseGroup g;
		g.addElement(new ParseSubject());
		g.addElement(new ParseDef());
		
		Language l;
		
		g.parse(p,l);
		
		return ":D";
	}
	catch (ParseException& pe)
	{
		std::cerr << pe << std::endl;
		return "";
	}

}

