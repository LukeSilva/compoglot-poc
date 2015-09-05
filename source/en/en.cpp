#include "en.h"
#include <iostream>

std::string en::GetSegment(std::ifstream& File)
{
	std::string Segment = "";
	if (File.good())
		std::getline(File,Segment);
	size_t pos;
	pos = Segment.find("_");
	if (pos != std::string::npos)
		Segment = Segment.substr(0,pos);

	return Segment;
}

bool en::GotoSegment(std::ifstream& File, int Segment)
{
	int ID = 0;
	int C = 0;
	while (ID < Segment)
	{
		if (File.good())
		{
			C = File.get();
			if (C=='_') ++ID;
			else if (C=='\n')
			{
				return true;
			}
		}
		else return true;
	}
	return false;
}


bool en::GotoLine(std::ifstream& File, int Line)
{
	std::string Temp;
	for (int LineNum = 1; LineNum < Line; ++LineNum)
	{
		if (File.good())
			std::getline(File,Temp);
		else return true;
	}
	return false;
}

std::string en::getNounString(noun* Noun, bool ObjCase)
{
#ifdef DEBUG
	std::cout << "[EN] getNounString(noun* Noun)" << std::endl;
	//printNoun("Noun",Noun);
#endif
	if (Noun->id==0) return "";
	std::string NounString = "";
	NounString += getNoun(Noun,ObjCase);
	return NounString;
}


std::string en::createSentence()
{
#ifdef DEBUG
	std::cout << "[EN] createSentence()" << std::endl;
#endif
	std::string Sentence = "";
	for (int i = 0; i < 16; ++i)
	{
#ifdef DEBUG
		std::cout << "[EN] Noun: " << i << std::endl;
#endif
		Sentence +=	getNounString(&s[i],false);
	}

	return Sentence;
}
