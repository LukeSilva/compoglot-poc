#include <iostream>
#include "ParseSubject.h"

// ---- Child Elements ----
#include "ParseNoun.h"

ParseGroup* ParseSubject::getGroup(Language& lang)
{
	ParseGroup* g = new ParseGroup();

	lang.NumFilledSubjects += 1;

	g->addElement(new ParseNoun(lang.Subjects[lang.NumFilledSubjects]));

	std::cout << "NUMFILLSUB: " << lang.NumFilledSubjects << std::endl;	

	return g;
}

bool ParseSubject::match(std::string name)
{
	if (name == "sub" || name == "Subject")
		return true;
	return false;
}


