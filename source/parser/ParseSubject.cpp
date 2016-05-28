#include <iostream>
#include "ParseSubject.h"

// ---- Child Elements ----
#include "ParseNoun.h"
#include "ParseAdjective.h"
#include "ParseIt.h"


ParseGroup* ParseSubject::getGroup(Language& lang)
{
	ParseGroup* g = new ParseGroup();

	lang.NumFilledSubjects += 1;

	g->addElement(new ParseNoun(lang.Subjects[lang.NumFilledSubjects]));
	g->addElement(new ParseAdjective(lang.Subjects[lang.NumFilledSubjects]));
	g->addElement(new ParseIt(lang.Subjects[lang.NumFilledSubjects]));

	return g;
}

bool ParseSubject::match(std::string name)
{
	if (name == "sub" || name == "Subject")
		return true;
	return false;
}


