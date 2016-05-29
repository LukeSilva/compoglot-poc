#include "ParseNounGroup.h"

//---- Child Elements ----
#include "ParseNoun.h"
#include "ParseAdjective.h"
#include "ParseIt.h"

ParseNounGroup::ParseNounGroup(Noun& n)
{
	addElement(new ParseNoun(n));
	addElement(new ParseAdjective(n));
	addElement(new ParseIt(n));
}
