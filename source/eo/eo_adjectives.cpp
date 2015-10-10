#include "../settings.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>

std::string eo::GetAdjective(Noun& n,int AdjectiveNum)
{
	if (AdjectiveNum < 1) return "";
	std::ifstream is(DICTIONARY EO_FOLDER "adjectives.txt");
	if (GotoLine(is,AdjectiveNum)) return "";
	std::string Adjective = GetSegment(is);
	Noun& NounObj = (n.ID == 0 || n.ID == 14) ? Subjects[0] : n;
	if (NounObj.IsPlural) Adjective += "j";
	if (NounObj.Data&0x01) Adjective += "n";
	
	return Adjective;
}