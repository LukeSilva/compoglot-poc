#include <memory>
#include <iostream>

#include "../Language.h"
#include "Parser.h"

//---- Child Elements ----
#include "ParseBasicVerb.h"
#include "ParseSubject.h"
#include "ParseSentenceType.h"
#include "ParseExtVerb.h"
#include "ParseObject.h"
#include "ParseProperties.h"
#include "ParseClause.h"

Parser::Parser()
{
	addElement(new ParseSubject());
	addElement(new ParseSentenceType());
	addElement(new ParseExtVerb());
	addElement(new ParseObject());
	addElement(new ParseProperties());
	addElement(new ParseClause());
}

void Parser::parseExt(std::string cmd, Language* lang, int verbNum)
{
	addElement(new ParseBasicVerb(verbNum));
	ParserIO p(cmd);
	p.skipWhitespace("beginning of input");
	
	parse(p, *lang);
}

std::string Parser::parse(std::string langid, std::string cmd)
{
	std::shared_ptr<Language> l = getLanguageFromStringID(langid);
	l->NewSentence();
	l->st = PRESENT_SIMPLE;
	try
	{
		ParserIO p(cmd);
		p.skipWhitespace("beginning of input");
		
		parse(p,*l);

		return l->createSentence();
	}
	catch (ParseException& pe)
	{
		std::cerr << pe << std::endl;
		return "";
	}

}

