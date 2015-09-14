#include "en.h"
#include "../parser/parser.h"
#include <iostream>

const std::string en::FutureTenseMarker = "will";

void en::ParseVerb(int verb,int n){
	std::ifstream is(DICTIONARY EN_EN_FOLDER "general");
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

bool en::IsVowel(char Letter)
{
	return (Letter == 'a' || Letter == 'e' || Letter == 'i' || Letter == 'o' || Letter == 'u');
}

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

std::string en::GetNounString(noun* Noun, bool ObjCase)
{
#ifdef DEBUG
	std::cout << "[EN] GetNounString(noun* Noun)" << std::endl;
#endif
	if (Noun->id==0) return "";
	std::string NounString = "";
	std::string NounResult = GetNoun(Noun,ObjCase);
	char FirstLetter = NounResult[0];
	std::string Article = GetArticle(Noun,IsVowel(FirstLetter));
	std::string Numeral = GetNumeral(Noun,false);
	if (Article.compare("")!=0)
		NounString+=Article + " ";
	if (Numeral.compare("")!=0)
		NounString+=Numeral + " ";
	NounString+=NounResult;
	return NounString;
}


std::string en::createSentence()
{
	if(verb1!=0){
		ParseVerb(0,verb1);
		verb1=0;
	}
	if (verb2!=0){
		ParseVerb(1,verb2);
		verb2=0;
	}
#ifdef DEBUG
	std::cout << "[EN] createSentence()" << std::endl;
#endif
	std::string Sentence = "";
	for (int i = 0; i < 16; ++i)
	{
#ifdef DEBUG
		std::cout << "[EN] Noun: " << i << std::endl;
#endif
		if (i!=0 && i < snum) Sentence +=", ";
		if (i==snum && snum >0) Sentence += " and ";
		Sentence +=	GetNounString(&s[i],false);
	}
	if (snum >= 0) Sentence += " ";
	if (v1 != 0)
		Sentence += GetVerb(s[0],snum,v1,st) + " ";
	return Sentence;
}
