#include "../settings.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>




std::string eo::GetConjunction(int ConjunctionNum)
{
	if (ConjunctionNum < 0) return "";
	std::ifstream is(DICTIONARY EO_FOLDER "conjunctions.txt");
	if(GotoLine(is,ConjunctionNum)) return "";
	std::string Conjunction = GetSegment(is);
	is.close();
	return Conjunction;
}



std::string eo::GetSubClause()
{
	std::string SubClauseString = GetConjunction(Conjunction);
	SubClauseString += " ";
	SubClause->IsClause = true;
	SubClauseString += SubClause->createSentence();
	return SubClauseString;
}
