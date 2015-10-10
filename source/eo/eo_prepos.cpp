#include "../settings.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>

std::string eo::GetPreposition(Noun& NounObj)
{
	if (NounObj.PreposNum < 1) return "";
	std::ifstream is (DICTIONARY EO_FOLDER "prepos.txt");
	if (GotoLine(is,NounObj.PreposNum)) return "";
	return GetSegment(is);
}