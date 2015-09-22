#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string en_Numerals[] = {"", "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

std::string en::GetNumeral(Noun* NounObj,bool ForceN)
{
#ifdef DEBUG
	std::cout << "[EN] GetNumeral(Noun* NounObj, bool ForceN = " << ForceN << " )" << std::endl;
#endif
	if (!ForceN && NounObj->Numeral <= 10 && NounObj->Numeral >= -10)
	{
		int ID = NounObj->Numeral < 0 ? -NounObj->Numeral : NounObj->Numeral;
		std::string Prefix = "";
		if (NounObj->Numeral < 0) Prefix = "negative ";
		return Prefix + en_Numerals[ID];
	} 
	else
	{
		std::ostringstream Stream;
		Stream << NounObj->Numeral;
		return Stream.str();
	}
	return "";
}
