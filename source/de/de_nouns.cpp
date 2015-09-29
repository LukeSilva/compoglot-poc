#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>

std::string de::GetNoun(Noun& n, int Case)
{
	std::ifstream is(DICTIONARY DE_FOLDER "nouns.txt");
	if (GotoLine(is, n.ID))
	{
		is.close();
		return "";
	}
	int NounType = is.get();
	if (NounType == 'P')
	{
			int c = (Case < 3) ? Case+1 : 3;
			if (n.IsReflexive) c = 4;
			if (GotoSegment(is,c))
			{
				is.close();
				return "";
			}
			std::string NounString = GetSegment(is);
			is.close();
			return NounString;
	}
	return "";
}



std::string de::GetNounString(Noun& n)
{
	return "";
}

