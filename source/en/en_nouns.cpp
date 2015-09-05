#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

std::string en::getNoun(noun* Noun,bool ObjCase)
{
#ifdef DEBUG
	std::cout << "[EN] getNoun(noun* Noun)" <<std::endl;
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
	return "";
}

