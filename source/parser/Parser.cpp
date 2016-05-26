#include <iostream>

#include "../Language.h"
#include "Parser.h"

#include "ParseBasicVerb.h"
#include "ParseSubject.h"
#include "ParseSentenceType.h"
#include "ParseExtVerb.h"

Parser::Parser()
{
	addElement(new ParseSubject());
	addElement(new ParseSentenceType());
	addElement(new ParseExtVerb());
}

void Parser::parseExt(std::string cmd, Language* lang, int verbNum)
{
	addElement(new ParseBasicVerb(verbNum));
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
		
		parse(p,*l);

		std::cout << "SENTENCE: \"" << l->createSentence() << "\"" << std::endl; 
		return l->createSentence();
	}
	catch (ParseException& pe)
	{
		std::cerr << pe << std::endl;
		return "";
	}

}

