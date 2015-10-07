#include "../settings.h"
#include "../parser/parser.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>

const std::string eo::And = "kaj";
const std::string eo::Or = "aŭ";

std::string eo::GetSegment(std::ifstream& File)
{
	std::string Segment = "";
	if (File.good())
		std::getline(File,Segment);
	return Segment;
}

bool eo::GotoLine(std::ifstream& File, int Line)
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

void eo::ParseVerb(int verb,int n)
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


std::string eo::createSentence()
{
	//return GetNoun(Subjects[0],false) + " " + GetNoun(Subjects[0],true);
	std::string Sentence;
	
	std::string SubjectString = "";
	for (int i = 0; i <= NumFilledSubjects; ++i)
	{
		
		if (i!=0 && i < NumFilledSubjects) SubjectString +=", ";
		if (i==NumFilledSubjects && NumFilledSubjects > 0 && SubConjunctionType == 0) SubjectString+= " " + And + " ";
		else if (i==NumFilledSubjects && NumFilledSubjects > 0 && SubConjunctionType == 1) SubjectString += " " + Or + " ";
		SubjectString += GetNoun(Subjects[i],false);
	}
	Sentence += SubjectString;
	return Sentence;
}