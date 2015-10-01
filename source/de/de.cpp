#include "../settings.h"
#include "../parser/parser.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>

const std::string de::Und = "und";
const std::string de::Oder = "oder";


std::string de::GetSegment(std::ifstream& File)
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

bool de::GotoSegment(std::ifstream& File, int Segment)
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

bool de::GotoLine(std::ifstream& File, int Line)
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

void de::ParseVerb(int verb,int n)
{
	std::ifstream is(DICTIONARY DE_FOLDER "extverbs.txt");
	if (GotoLine(is,n)) return;
	std::string Line;
	std::getline(is,Line);
	is.close();
	Parser* p=new Parser; 
	p->string=(char*)Line.c_str();
	p->ptr=0;
	p->lookptr=0;
	p->look=Line[0];
	p->verb=verb;
	p->expect('(',__FILE__,__LINE__);
	p->_parse(this);
 
}

std::string de::createSentence()
{
	StartVerb = "";
	EndVerbs = "";
	//First of all, parse the ExtVerb files
	if(ExtVerb1!=0){
		ParseVerb(0,ExtVerb1);
		ExtVerb1=0;
	}
	if (ExtVerb2!=0){
		ParseVerb(1,ExtVerb2);
		ExtVerb2=0;
	}
	
	FillVerbs(Subjects[0],Verb1);
	
	std::string SentenceString = "";
	
	
	for (int i = 0; i <= NumFilledSubjects; ++i)
	{
		
		if (i!=0 && i < NumFilledSubjects) SentenceString +=", ";
		if (i==NumFilledSubjects && NumFilledSubjects > 0 && SubConjunctionType == 0) SentenceString+= " " + Und + " ";
		else if (i==NumFilledSubjects && NumFilledSubjects > 0 && SubConjunctionType == 1) SentenceString += " " + Oder + " ";
		SentenceString += GetNounString(Subjects[i]);
	}
	
	if (NumFilledSubjects >= 0) SentenceString += " ";
	
	SentenceString += StartVerb + " ";
	
	
	SentenceString += EndVerbs;
	
	return SentenceString;

}
