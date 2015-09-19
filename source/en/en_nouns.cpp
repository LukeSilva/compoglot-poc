#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

std::string en::GetNounString(noun* Noun, bool ObjCase)
{
	if (Noun->id==0) return "";
#ifdef DEBUG
	std::cout << "[EN] GetNounString(noun* Noun)" << std::endl;
#endif
	std::string NounString = "";
	std::string NounResult = GetNoun(Noun,ObjCase);
	char FirstLetter = NounResult[0];
	std::string Article = GetArticle(Noun,IsVowel(FirstLetter));
	std::string Numeral = GetNumeral(Noun,false);
	std::string Prepos = GetPrepos(Noun->prepos);
	if (Prepos.compare("")!=0)
		NounString+=Prepos + " ";
	if (Article.compare("")!=0)
		NounString+=Article + " ";
	if (Numeral.compare("")!=0)
		NounString+=Numeral + " ";
	NounString+=NounResult;
	if (Noun->usegenitive)
	{
		NounString += " " + GenitiveMarker + " ";
		NounString += GetNounString(Noun->genitivenoun,true);
	}
	return NounString;
}

std::string en::GetNoun(noun* Noun,bool ObjCase)
{
#ifdef DEBUG
	std::cout << "[EN] GetNoun(noun* Noun)" <<std::endl;
#endif
	std::ifstream is(DICTIONARY EN_FOLDER "nouns");
	if (GotoLine(is,Noun->id)) return "";
	int Typ = is.get();
	//d,f,m,n,o
	if (Typ == 'd')
	{
		int GetID = 1;
		if (ObjCase && Noun->reflex) GetID = 4;
		else if (ObjCase) GetID = 2;
		if (GotoSegment(is,GetID)) return "";
		return GetSegment(is);
	}
	else if (Typ == 'n' || Typ == 'm' || Typ == 'f')
	{
		if (GotoSegment(is,1)) return "";
		std::string Base = GetSegment(is);
		if (Noun->plural) Base += "s";
		return Base;
	}
	else if (Typ == 'o')
	{
		int GetID = 1;
		if (Noun->plural)
			GetID = 2;
		if (GotoSegment(is,GetID)) return "";
		return GetSegment(is);
	}
	return "";
}

