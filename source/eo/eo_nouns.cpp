#include "../settings.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>



std::string eo::GetNoun(Noun& n, bool Accusative)
{
	std::ifstream is(DICTIONARY EO_FOLDER "nouns.txt");
	if (GotoLine(is,n.ID))
		return "";
	std::string Segment = GetSegment(is);
	if (n.IsPlural) Segment += "j";
	if (Accusative) Segment += "n";
	return Segment;
}

std::string eo::GetNounString(Noun& n)
{
	std::string NounString = GetNoun(n,n.Data);
	std::string ArticleString = GetArticle(n);
	std::string Complete;
	std::string NumeralString = GetNumeral(n,false);
	std::string Preposition = GetPreposition(n);
	if (Preposition.compare(""))
		Complete += Preposition + " ";
	if (ArticleString.compare(""))
		Complete += ArticleString + " ";
	if (NumeralString.compare(""))
		Complete += NumeralString + " ";
	
	for (int i = 0; i < 16; ++i)
	{
		std::string Adjective = GetAdjective(n,n.Adjectives[i]);
		if (Adjective.compare("")) 
			Complete += Adjective + " ";
	}
	
	Complete += NounString;
	
	if (n.ShouldUseRelativeClause)
	{
		int CaseRMarker = 0;
		if (n.RelativeClauseObj != 0)
			CaseRMarker = n.RelativeClause->Objects[n.RelativeClauseObj-1][0].Data;
		else
			CaseRMarker = n.RelativeClause->Subjects[0].Data;
		
		std::string RelativeClauseString = "";
		RelativeClauseString += std::string("kiu") + (n.IsPlural ? "j" : "") + (CaseRMarker ? "n" : "");
		RelativeClauseString += " " + n.RelativeClause->createSentence();
		Complete += ", " + RelativeClauseString;
	}
	
	return Complete;
}