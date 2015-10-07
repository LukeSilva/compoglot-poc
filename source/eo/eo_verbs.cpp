#include "../settings.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>


const std::string eo::VerbEndings[9] = { "i","as","is","os","us","u","ata","ita","ota" };


std::string eo::GetVerbForm(int VerbNum,VerbForms VerbForm)
{
	std::ifstream is(DICTIONARY EO_FOLDER "verbs.txt");
	if (GotoLine(is,VerbNum)) return "";
	std::string VerbString = GetSegment(is);
	VerbString += VerbEndings[VerbForm];
	return VerbString;
}


std::string eo::GetVerb(int VerbNum)
{
	if (st >= 0 && st <= 1)
		return GetVerbForm(VerbNum,FORM_PRESENT);
	else if (st >= 2 && st <= 9)
		return GetVerbForm(VerbNum,FORM_PAST);
	else if (st >= 10 && st <= 15)
		return GetVerbForm(VerbNum,FORM_FUTURE);
	else if (st >= 16 && st <= 17)
		return GetVerbForm(1,FORM_PRESENT) + " " + GetVerbForm(VerbNum,FORM_PRESENT_PASSIVE_PARTICIPLE);
	else if (st >= 18 && st <= 25)
		return GetVerbForm(1,FORM_PAST) + " " + GetVerbForm(VerbNum, FORM_PAST_PASSIVE_PARTICIPLE);
	else if (st >= 26 && st <= 31)
		return GetVerbForm(1,FORM_FUTURE) + " " + GetVerbForm(VerbNum, FORM_FUTURE_PASSIVE_PARTICIPLE);
	return "";
}