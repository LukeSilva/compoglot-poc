#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>

std::string de::GetSubClause()
{
	if (Conjunction < 0) return "";
	
	std::ifstream is(DICTIONARY DE_FOLDER "conjunctions.txt");
	if (GotoLine(is,Conjunction)) return "";
	int Data = is.get();
	if (GotoSegment(is,1)) return "";
	std::string ConjunctionString = GetSegment(is);
	is.get();
	if (Data == '0')
		SubClause->IsClause = true;
	else if (Data == '2')
		SubClause->Data |= 1;
	SubClause->Punctuation = 0;
	SubClause->Capital = false;
	
	std::string ClauseString = SubClause->createSentence();
	
	return ", " + ConjunctionString + " " + ClauseString;
}