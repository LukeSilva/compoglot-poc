#include "en.h"
#include "../parser/parser.h"
#include <iostream>

const std::string en::FutureTenseMarker = "will";
const std::string en::GenitiveMarker = "of";
const std::string en::RClausePersonalMarker = "who";
const std::string en::RClauseEssentialMarker = "that";
const std::string en::RClauseNonEssentialMarker = "which";
const std::string en::QuestionMarkers[6] = {"who","what","when","where","why","how"};

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
	if(ExtVerb1!=0){
		ParseVerb(0,ExtVerb1);
		ExtVerb1=0;
	}
	if (ExtVerb2!=0){
		ParseVerb(1,ExtVerb2);
		ExtVerb2=0;
	}

	//Create blank sentence
	std::string Sentence = "";

	if (Question > 1)
	{
		Sentence += QuestionMarkers[Question-2] + " ";
	}

	//Store the subjects in a different string
	std::string SubjectString = "";

	//Loop through the subjects, adding them
	for (int i = 0; i <= NumFilledSubjects; ++i)
	{
		if (i!=0 && i < NumFilledSubjects) SubjectString +=", ";
		if (i==NumFilledSubjects && NumFilledSubjects > 0) SubjectString += " and ";
		SubjectString +=	GetNounString(&Subjects[i],false);
	}

	
	std::string Mid = "";
	
	if (Question>=1)
	{
		Mid = SubjectString;
	}
	else
	{
		Sentence += SubjectString;
		//If there is a subject, insert a space beteen the subjects and the verb.
		if (NumFilledSubjects >= 0) Sentence += " ";
	}


	//Add the first verb to the sentence, if it exists
	if (Verb1 != 0)
		Sentence += GetVerb(Subjects[0],NumFilledSubjects,Verb1,st,Mid) + " ";

	//Add the second verb to the sentenc, if it exists
	if (Verb2 != 0)
		Sentence += GetOtherVerb(Verb1,Verb2) + " ";

	//Loop through the objects, adding them to the sentence
	for (int objid = 0; objid < 8; ++objid)
	{
		for (int i = 0; i <= NumFilledObjects[objid]; ++i)
		{
			if (i != 0 && i < NumFilledObjects[objid]) Sentence += ", ";
			if (NumFilledObjects[objid] > 0 && i == NumFilledObjects[objid]) Sentence += " and ";
			Sentence += GetNounString(&Objects[objid][i],true);
		}
		if (NumFilledObjects[objid]>=0) Sentence += " ";
	}

	//If a conjunction and subclause exists, create the subclause, and add it to the sentence.
	if (SubClause!=NULL && Conjunction != 0)
	{
		Sentence += GetSubClause() + " ";
	}

	if(Sentence.compare("")!=0)
		Sentence.pop_back();
	if (Punctuation && !IsClause)
	{
		if (Question==0)
			Sentence+=".";
		else
			Sentence+="?";
	}

	if (Capital && !IsClause)
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
