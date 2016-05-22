#include "../settings.h"
#include "../parser/Parser.h"
#include "eo.h"
#include <string>
#include <iostream>
#include <fstream>

const std::string eo::And = "kaj";
const std::string eo::Or = "aŭ";
const std::string eo::GenitiveMarker = "de";


std::string eo::GetSegment(std::ifstream& File)
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
	std::ifstream is(DICTIONARY EO_FOLDER "extverbs.txt");
	if (GotoLine(is,n)) return;
	std::string Line;
	std::getline(is,Line);
	is.close();
	Parser p;
	p.parseExt(Line,this);
 
}


std::string eo::createSentence()
{
	
	if(ExtVerb1!=0){
		ParseVerb(0,ExtVerb1);
		ExtVerb1=0;
	}
	if (ExtVerb2!=0){
		ParseVerb(1,ExtVerb2);
		ExtVerb2=0;
	}
	
	std::string Sentence;
	
	std::string SubjectString = "";
	
	std::string Verbs;
	
	
	if (Verb1 > 0)
		Verbs += GetVerb(Verb1) + " ";
	if (Verb2 > 0)
		Verbs += GetVerbForm(Verb2,FORM_INFINITIVE) + " ";
	
	if (Question == 1)
		Sentence += "Cû ";
	
	for (int i = 0; i <= NumFilledSubjects; ++i)
	{
		
		if (i!=0 && i < NumFilledSubjects) SubjectString +=", ";
		if (i==NumFilledSubjects && NumFilledSubjects > 0 && SubConjunctionType == 0) SubjectString+= " " + And + " ";
		else if (i==NumFilledSubjects && NumFilledSubjects > 0 && SubConjunctionType == 1) SubjectString += " " + Or + " ";
		SubjectString += GetNounString(Subjects[i]);
	}
	if (SubjectString.compare("")!=0)
		Sentence += SubjectString + " ";
	
	if (st != BUTTON_TEXT)
		Sentence += Verbs;
	else
		Sentence += GetVerbForm(Verb1,FORM_INFINITIVE) + " ";
	
		//Loop through the objects, adding them to the sentence
	for (int objid = 0; objid < 8; ++objid)
	{
		for (int i = 0; i <= NumFilledObjects[objid]; ++i)
		{
			if (i != 0 && i < NumFilledObjects[objid]) Sentence += ", ";
			if (i==NumFilledObjects[objid] && NumFilledObjects[objid] > 0 && ObjConjunctionType[objid] == 0) Sentence+= " " + And + " ";
			else if (i==NumFilledObjects[objid]&& NumFilledObjects[objid]> 0 && ObjConjunctionType[objid] == 1) Sentence += " " + Or + " ";
			Sentence += GetNounString(Objects[objid][i]);
		}
		if (NumFilledObjects[objid]>=0) Sentence += " ";
	}
	
	if (SubClause!=NULL && Conjunction != 0)
	{
		Sentence += GetSubClause() + " ";
	}
	
	while (Sentence[Sentence.length()-1]==' ')
		Sentence.pop_back();
	
	if	(Punctuation && !IsClause)
	{
		if (Question==0)
			Sentence+=".";
		else
			Sentence+="?";
	}
	
	if (Capital && !IsClause && Sentence.length() > 0)
	{
		char FirstLetter = Sentence.at(0);
		
		if (FirstLetter >= 'a' && FirstLetter <= 'z')
		{
			FirstLetter -= ('a' - 'A');
			Sentence[0] = FirstLetter;
		}
	}

	return Sentence;
}
