#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>

std::string de::GetNoun(Noun& n, int Case)
{
	std::ifstream is(DICTIONARY DE_FOLDER "nouns");
	GotoLine(is, n.ID);
	return "";
}



std::string de::GetNounString(Noun& n)
{
	return "";
}

