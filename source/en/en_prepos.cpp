#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

std::string en::GetPrepos(int PreposNum)
{
	if (PreposNum == 0)	return "";
#ifdef DEBUG
	std::cout << "[EN] GetPrepos(int PreposNum = " << PreposNum << " )" << std::endl;
#endif
	std::ifstream is(DICTIONARY EN_EN_FOLDER "prepos");
	if(GotoLine(is,PreposNum)) return "";
	std::string Preposition = GetSegment(is);
	is.close();
	return Preposition;
}
