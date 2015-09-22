#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

int en::GetNounType(int NounNum)
{
	if (NounNum < 0) return 0;
#ifdef DEBUG
	std::cout << "[EN] GetNounType(int NounNum = " << NounNum << " )" << std::endl;
#endif
	std::ifstream is(DICTIONARY EN_EN_FOLDER "nouns");
	GotoLine(is,NounNum);
	int Data = is.get();
	is.close();
	return Data;
}

std::string en::GetNounString(Noun* NounObj, bool ObjCase)
{
	if (NounObj->ID==0) return "";
#ifdef DEBUG
	std::cout << "[EN] GetNounString(Noun* NounObj)" << std::endl;
#endif
	//Create the final string that will be returned. (Empty for now).
	std::string NounString = "";

	//Create the string that will be inserted before the articles (so that we can correctly turn 'a' into 'an' if this begins with a vowel)
	std::string NounResult;
	
	//Prepend all the adjectives to the NounResult, if the adjectives exist.
	for (int i = 0; i < 16; ++i)
	{
		std::string Adjective = GetAdjective(NounObj->Adjectives[i]);
		if (Adjective.compare("")!=0)
			NounResult += Adjective + " ";
	}

	//Prepend the Noun to NounResult.
	NounResult += GetNoun(NounObj,ObjCase);

	//Get the string of the article, telling it to turn 'a' into 'an' if NounResult begins with a vowel.
	std::string Article = GetArticle(NounObj,IsVowel(NounResult[0]));

	//Get the numberal
	std::string Numeral = GetNumeral(NounObj,false);

	//Get the preposition
	std::string Prepos = GetPrepos(NounObj->PreposNum);

	//Start the NounString with the preposition if necessary
	if (Prepos.compare("")!=0)
		NounString+=Prepos + " ";

	//Add the article
	if (Article.compare("")!=0)
		NounString+=Article + " ";

	//Add the Numeral. This is not currently added to noun result, and shouldn't matter as you shouldn't be adding a numeral when you use a/an
	if (Numeral.compare("")!=0)
		NounString+=Numeral + " ";

	//Add the noun result to the noun string (adjectives, and noun)
	NounString+=NounResult;

	//If there is a genitive object, add it.
	if (NounObj->ShouldUseGenitive)
	{
		NounString += " " + GenitiveMarker + " ";
		NounString += GetNounString(NounObj->GenitiveNoun,true);
	}

	//If there is a relative clause, add it.
	if (NounObj->ShouldUseRelativeClause)
	{
		NounObj->RelativeClause->IsClause = true;
		
		//If the relative clause is about a persion, use "who"
		int NounType = GetNounType(NounObj->ID);
		if (NounType == 'm' || NounType == 'f' || NounType == 'p' || NounType == 'd')
		{
			NounString += " " + RClausePersonalMarker;	
		}
		//Otherwise if the relative clause is essential use "that"
		else if (NounObj->IsRelativeClauseEssential) NounString += " " + RClauseEssentialMarker;
		//Otherwise (non essential) use "which"
		else NounString += " " + RClauseNonEssentialMarker;
		
		//Append the clause
		NounString += " " + NounObj->RelativeClause->createSentence();
	}

	//Return the result.
	return NounString;
}

std::string en::GetNoun(Noun* NounObj,bool ObjCase)
{
#ifdef DEBUG
	std::cout << "[EN] GetNoun(noun* NounObj)" <<std::endl;
#endif
	std::ifstream is(DICTIONARY EN_FOLDER "nouns");
	if (GotoLine(is,NounObj->ID)) return "";
	int Typ = is.get();
	if (Typ == 'd')
	{
		int GetID = 1;
		if (ObjCase && NounObj->IsReflexive) GetID = 4;
		else if (ObjCase) GetID = 2;
		if (GotoSegment(is,GetID)) return "";
		return GetSegment(is);
	}
	else if (Typ == 'n' || Typ == 'm' || Typ == 'f')
	{
		if (GotoSegment(is,1)) return "";
		std::string Base = GetSegment(is);
		if (NounObj->IsPlural) Base += "s";
		return Base;
	}
	else if (Typ == 'o')
	{
		int GetID = 1;
		if (NounObj->IsPlural)
			GetID = 2;
		if (GotoSegment(is,GetID)) return "";
		return GetSegment(is);
	}
	return "";
}

