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