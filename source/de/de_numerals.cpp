#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


const std::string de::Numerals[12] = {"", "null", "ein", "zwei", "drei", "vier", "fünf", "sechs", "sieben", "acht", "neun", "zehn"};

std::string de::GetNumeral(Noun& n)
{
	if (n.Numeral <= 10 && n.Numeral >= -10)
	{
		int ID = n.Numeral < 0 ? -n.Numeral : n.Numeral;
		std::string Prefix = "";
		if (n.Numeral < 0) Prefix = "negativ ";
		std::string NumeralString = Numerals[ID];
		if (ID == 2)
		{
			Noun a = n;
			a.ArticleType = -2;
			NumeralString = GetArticle(a);
			
		}
		return Prefix + NumeralString;
	} 
	else
	{
		std::ostringstream Stream;
		Stream << n.Numeral + ((n.Numeral < 0) ? 1 : -1);
		return Stream.str();
	}
	return "";

}