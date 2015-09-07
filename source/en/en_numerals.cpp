#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

std::string en_Numerals[] = {"", "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

std::string en::GetNumeral(noun* Noun,bool ForceN)
{
	if (!ForceN && Noun->num <= 10 && Noun->num >= -10)
	{
		int ID = Noun->num < 0 ? -Noun->num : Noun->num;
		std::string Prefix = "";
		if (Noun->num < 0) Prefix = "negative ";
		return Prefix + en_Numerals[ID];
	} 
	else
	{
		std::ostringstream Stream;
		Stream << Noun->num;
		return Stream.str();
	}
	return "";
}
