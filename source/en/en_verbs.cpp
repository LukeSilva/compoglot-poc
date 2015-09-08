#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


std::string en::GetVerbSimplePresent(int VerbForm, int VerbNum)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerbSimplePresent(int VerbForm = " << VerbForm << " , int VerbNum = " << VerbNum << " ) " << std::endl;
#endif
	std::ifstream is(DICTIONARY EN_EN_FOLDER "verb_present");
	if (GotoLine(is,VerbNum)) return "";
	int Data = is.get();
	if (Data == '0')
	{
		if (GotoSegment(is,VerbForm+1)) return "";
		return GetSegment(is);
	}
	else
	{
		if (GotoSegment(is,1)) return "";
		std::string Segment = GetSegment(is);
		if (Data != '3')
		{
			if (VerbForm > 2 && VerbForm < 6)
			{
				//Need to add 's' conjugation
				int u = Segment.length();
				if (Segment[u-1]=='o' || (Segment[u-1]=='s' && Segment[u-2]=='s') || (Segment[u-1]=='h' && Segment[u-2]=='s') || (Segment[u-1]=='h' && Segment[u-2]=='c') || (Segment[u-1]=='z' && Segment[u-2]=='z') || Segment[u-1]=='x')
				{
					Segment +="e";
				}
				Segment += "s";
			}
		}
		return Segment;
	}
	return "";
}

std::string en::GetVerb(noun& Noun, int snum, int VerbNum, int SentenceType)
{
#ifdef DEBUG
	std::cout << "[EN] GetVerb(noun& Noun, int snum = " << snum << " , int VerbNum = " << VerbNum << " , int SentenceType = " << SentenceType << " )" << std::endl;
#endif
	//First we need to figure out which form of a verb we need.
	//We can do this with Noun and snum information.
	//Then we need to get the verb string from the appropriate function, and return it.
	//We can do this with VerbNum and SentenceType information.
	int VerbForm;
	if (Noun.id < 10 && Noun.id > 0) VerbForm = Noun.id;
	else if (snum > 0 || Noun.plural) VerbForm = 8;
	else if (snum < 0) VerbForm = 0;
	else VerbForm = 5;
#ifdef DEBUG
	std::cout << "[EN] VerbForm = " << VerbForm << std::endl;
#endif
	return GetVerbSimplePresent(VerbForm,VerbNum);
}
