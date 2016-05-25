#include <iostream>

#include "../Language.h"
#include "Parser.h"

#include "ParseGroup.h"
#include "ParseSubject.h"
#include "ParseSentenceType.h"

void Parser::parseExt(std::string cmd, Language* lang)
{
}

std::string Parser::parse(std::string langid, std::string cmd)
{
	Language *l = getLanguageFromStringID(langid);
	l->NewSentence();
	l->st = PRESENT_SIMPLE;
	try
	{
		ParserIO p(cmd);
		p.skipWhitespace("beginning of input");
		
		ParseGroup g;
		g.addElement(new ParseSubject());
		g.addElement(new ParseSentenceType());
		
		g.parse(p,*l);
		std::cout << "SENTENCE: \"" << l->createSentence() << "\"" << std::endl; 
		return l->createSentence();
	}
	catch (ParseException& pe)
	{
		std::cerr << pe << std::endl;
		return "";
	}

}

