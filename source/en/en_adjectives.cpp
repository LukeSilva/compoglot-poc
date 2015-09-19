#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

std::string en::GetAdjective(int AdjectiveNum)
{
	if (AdjectiveNum <= 0 ) return "";
#ifdef DEBUG
	std::cout << "[EN] GetAdjective(int AdjectiveNum = " << AdjectiveNum << " )" << std::endl;
#endif
	std::ifstream is(DICTIONARY EN_EN_FOLDER "adjectives");
	if (GotoLine(is,AdjectiveNum)) return "";
	std::string Adjective = GetSegment(is);
	is.close();
	return Adjective;
}
