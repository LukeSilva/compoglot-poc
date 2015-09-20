#include "en.h"
#include "../parser/parser.h"
#include <iostream>

const std::string en::FutureTenseMarker = "will";
const std::string en::GenitiveMarker = "of";
const std::string en::RClausePersonalMarker = "who";
const std::string en::RClauseEssentialMarker = "that";
const std::string en::RClauseNonEssentialMarker = "which";

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

std::string en::createSentence()
{
	//First of all, parse the ExtVerb files
	if(verb1!=0){
		ParseVerb(0,verb1);
		verb1=0;
	}
	if (verb2!=0){
		ParseVerb(1,verb2);
		verb2=0;
	}

	//Print debugging information, if enabled
#ifdef DEBUG
	std::cout << "[EN] createSentence()" << std::endl;
#endif

	//Create blank sentence
	std::string Sentence = "";

	//Loop through the subjects, adding them to the sentence
	for (int i = 0; i < 16; ++i)
	{
#ifdef DEBUG
		if (s[i].id!=0)
			std::cout << "[EN] Noun: " << i << std::endl;
#endif
		if (i!=0 && i < snum) Sentence +=", ";
		if (i==snum && snum >0) Sentence += " and ";
		Sentence +=	GetNounString(&s[i],false);
	}

	//If there is a subject, insert a space beteen the subjects and the verb.
	if (snum >= 0) Sentence += " ";

	//Add the first verb to the sentence, if it exists
	if (v1 != 0)
		Sentence += GetVerb(s[0],snum,v1,st) + " ";

	//Add the second verb to the sentenc, if it exists
	if (v2 != 0)
		Sentence += GetOtherVerb(v1,v2) + " ";

	//Loop through the objects, adding them to the sentence
	for (int objid = 0; objid < 8; ++objid)
	{
		for (int i = 0; i < 16; ++i)
		{
#ifdef DEBUG
			if (obj[objid][i].id!=0)
				std::cout << "[EN] Obj " << objid << " Noun: " << i << std::endl;
#endif
			if (i != 0 && i < objnum[objid]) Sentence += ", ";
			if (objnum[objid] > 0 && i == objnum[objid]) Sentence += " and ";
			Sentence += GetNounString(&obj[objid][i],true);
		}
		if (objnum[objid]>=0) Sentence += " ";
	}

	//If a conjunction and subclause exists, create the subclause, and add it to the sentence.
	if (subClause!=NULL && conjunction != 0)
	{
		Sentence += GetSubClause() + " ";
	}
	
	Sentence.pop_back();
	if (punctuation)
	{
		Sentence+=".";
	}

	if (Capital)
	{
		int FirstLetter = Sentence.at(0);
		if (FirstLetter >= 'a' && FirstLetter <= 'z')
		{
			FirstLetter -= ('a' - 'A');
			Sentence[0] = FirstLetter;
		}
	}	
		
	return Sentence;
}
