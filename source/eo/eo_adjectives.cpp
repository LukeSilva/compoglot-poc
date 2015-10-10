#include "../settings.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>

std::string eo::GetAdjective(Noun& NounObj,int AdjectiveNum)
{
	if (AdjectiveNum < 1) return "";
	std::ifstream is(DICTIONARY EO_FOLDER "adjectives.txt");
	if (GotoLine(is,AdjectiveNum)) return "";
	std::string Adjective = GetSegment(is);
	
	if (NounObj.ID == 0 || NounObj.ID == 14)
		NounObj = Subjects[0];
	if (NounObj.IsPlural) Adjective += "j";
	if (NounObj.Data&0x01) Adjective += "n";
	
	return Adjective;
}