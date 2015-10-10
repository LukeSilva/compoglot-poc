#include "../settings.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

const std::string eo::Numerals[12] = {"","nulo","unu","du","tri","kvar","kvin","ses","sep","ok","naŭ","dek"};

std::string eo::GetNumeral(Noun& NounObj, bool ForceN)
{
	if (!ForceN && NounObj.Numeral <= 10 && NounObj.Numeral >= -10)
	{
		int ID = NounObj.Numeral < 0 ? -NounObj.Numeral : NounObj.Numeral;
		std::string Prefix = "";
		if (NounObj.Numeral < 0) Prefix = "malpositva ";
		return Prefix + Numerals[ID];
	} 
	else
	{
		std::ostringstream Stream;
		Stream << NounObj.Numeral + ((NounObj.Numeral < 0) ? 1 : -1);
		return Stream.str();
	}
	return "";
}