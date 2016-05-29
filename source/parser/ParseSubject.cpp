#include <iostream>
#include "ParseSubject.h"

#include "ParseNounGroup.h"


ParseGroup* ParseSubject::getGroup(Language& lang)
{

	lang.NumFilledSubjects += 1;

	return new ParseNounGroup(lang.Subjects[lang.NumFilledSubjects]);
}

bool ParseSubject::match(std::string name)
{
	if (name == "sub" || name == "Subject")
		return true;
	return false;
}


