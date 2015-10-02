#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

std::string en::GetConjunction(int ConjunctionNum)
{
	if (ConjunctionNum < 0) return "";
	std::ifstream is(DICTIONARY EN_EN_FOLDER "conjunctions");
	if(GotoLine(is,ConjunctionNum)) return "";
	std::string Conjunction = GetSegment(is);
	is.close();
	return Conjunction;
}


std::string en::GetSubClause()
{
	std::string SubClauseString = GetConjunction(Conjunction);
	SubClauseString += " ";
	SubClause->IsClause = true;
	SubClauseString += SubClause->createSentence();
	return SubClauseString;
}
