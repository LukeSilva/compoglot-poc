#include "parser.h"
#include "../Language.h"
#include <stdio.h>
#include <stdlib.h>
#include "../settings.h"
Noun* Parser::parseNoun(){
	Noun* n = new Noun;
	n->ID = getInt();
	n->Data = 0;
	expect(',',__FILE__,__LINE__);
	n->Numeral = getInt();
	expect(',',__FILE__,__LINE__);
	if (rstLook() && check("true"))
		n->IsReflexive=true;
	else if (rstLook() && check("false"))
		n->IsReflexive=false;
	else error("Couldn't parse boolean",__FILE__,__LINE__);
		expect(',',__FILE__,__LINE__);
	if (rstLook() && check("true"))
		n->IsPlural=true;
	else if (rstLook() && check("false"))
		n->IsPlural=false;
	else error("Couldn't parse boolean",__FILE__,__LINE__);
	expect(',',__FILE__,__LINE__);
	n->ArticleType = getInt();
	expect(',',__FILE__,__LINE__);
	if (rstLook() && check("true"))
		n->ShouldUseGenitive=true;
	else if (rstLook() && check("false"))
		n->ShouldUseGenitive=false;
	else error("Couldn't parse boolean (genitive-bool)",__FILE__,__LINE__);
	if (n->ShouldUseGenitive==true)
	{
		expect(',',__FILE__,__LINE__);
		expect('n',__FILE__,__LINE__);
		expect('(',__FILE__,__LINE__);
		n->GenitiveNoun = parseNoun();
		expect(')',__FILE__,__LINE__);
	}
	expect(',',__FILE__,__LINE__);
	if (rstLook() && check("true"))
	{
		expect(',',__FILE__,__LINE__);
		n->PreposNum = getInt();
	}
	else if (rstLook() && check("false"))
		n->PreposNum = 0;
	else error("Couldn't parse boolean (preposition-bool)",__FILE__,__LINE__);
	expect(',',__FILE__,__LINE__);
	if (rstLook() && check("true"))
	{
		expect(',',__FILE__,__LINE__);
		if (rstLook() && check("true"))
		{
			n->IsRelativeClauseEssential = true;
		}
		else if (rstLook() && check("false"))
		{
			n->IsRelativeClauseEssential = false;
		}
		else error("Couldn't parse boolean (rClause-Essential-bool)",__FILE__,__LINE__);
		expect(',',__FILE__,__LINE__);
		n->RelativeClauseObj = getInt();
		expect(',',__FILE__,__LINE__);
		expect('(',__FILE__,__LINE__);
		Language* nlang = getLanguageFromStringId(langid);
		nlang->NewSentence();
		nlang->Subjects[0].ID = 14;
		nlang->Subjects[0].IsPlural=n->IsPlural;
		nlang->NumFilledSubjects = 0;	
		_parse(nlang);
		nlang->Punctuation = false;
		n->RelativeClause = nlang;
		n->ShouldUseRelativeClause = true;
	}
	else if (rstLook() && check("false"))
	{
		n->ShouldUseRelativeClause = false;
	}
	else error("Couldn't parse boolean (rClause-bool)",__FILE__,__LINE__);
	if (n->Numeral>2 || n->Numeral<-2)
		n->IsPlural = true;
	for (int i = 0; i < 16; ++i)
	{
		n->Adjectives[i]=0;
	}
	return n;
}

