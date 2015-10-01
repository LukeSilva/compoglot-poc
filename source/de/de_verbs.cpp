#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>

std::string de::GetVerbPresentSimple(int VerbForm, int VerbNum)
{
	std::ifstream is( DICTIONARY DE_FOLDER "verb_present.txt");
	if (GotoLine(is,VerbNum)) return "";
	int Data = is.get();
	if (Data == '0')
	{
		if (GotoSegment(is,VerbForm+1)) return "";
		std::string Segment = GetSegment(is);
		is.close();
		return Segment;
	}
	else
	{
		if (GotoSegment(is,1)) return "";
		std::string RootVerb = GetSegment(is);
		is.close();
		
		if (!(VerbForm == 0 || VerbForm == 6 || VerbForm == 8 || VerbForm == 9))
		{
			if (RootVerb[RootVerb.length()-1]=='n')
				RootVerb.pop_back();
			if (RootVerb[RootVerb.length()-1]=='e')
				RootVerb.pop_back();
		}
		
		std::string ConjVerb = RootVerb;
		if (VerbForm == 1) //Ich
			ConjVerb += "e";
		else if (VerbForm == 2) //Du
			ConjVerb += "st";
		else if (VerbForm == 3 || VerbForm == 4 || VerbForm == 5 || VerbForm == 7) // er/sie/es/ihr
			ConjVerb += "t";
		
		return ConjVerb;
	}
	
	is.close();
	return "";
	
}

std::string de::GetVerbPastParticiple(int VerbNum)
{
	std::ifstream is(DICTIONARY DE_FOLDER "verb_pastperfekt.txt");
	if (GotoLine(is,VerbNum)) return "";
	if (GotoSegment(is,1)) return "";
	std::string Segment = GetSegment(is);
	return Segment;
}

void de::FillVerbPastPerfekt(int VerbForm, int VerbNum)
{
	std::ifstream is(DICTIONARY DE_FOLDER "verb_pastperfekt.txt");
	if (GotoLine(is,VerbNum)) return;
	int Data = is.get();
	is.close();
	if (Data == '0')
		StartVerb = GetVerbPresentSimple(VerbForm,2);
	else if (Data == '1')
		StartVerb = GetVerbPresentSimple(VerbForm,1);
	
	EndVerbs += GetVerbPastParticiple(VerbNum);	
}

std::string de::GetVerbPastSimple(int VerbForm, int VerbNum)
{
	std::ifstream is(DICTIONARY DE_FOLDER "verb_simple.txt");
	if (GotoLine(is,VerbNum)) return "";
	int Data = is.get();
	if (Data == '1')
	{
		is.close();
		FillVerbPastPerfekt(VerbForm,VerbNum);
		return StartVerb;
	}
	if (GotoSegment(is,1)) return "";
	std::string Segment = GetSegment(is);
	is.close();
	if (VerbForm == 2)
		Segment += "st";
	else if (VerbForm == 6 || VerbForm == 8 || VerbForm == 9)
	{
		if (Segment[Segment.length()-1]!='e')
			Segment += "e";
		Segment += "n";
	}
	else if (VerbForm == 7)
		Segment += "t";
	
	return Segment;
}

void de::FillVerbFuture(int VerbForm, int VerbNum)
{
	StartVerb = GetVerbPresentSimple(VerbForm,14);
	EndVerbs += GetVerbPresentSimple(0,VerbNum);
}

void de::FillVerbFuturePerfekt(int VerbForm, int VerbNum)
{
	FillVerbPastPerfekt(0,VerbNum);
	EndVerbs += " " + StartVerb;
	StartVerb = GetVerbPresentSimple(VerbForm,14);
}

void de::FillVerbPassivePresent(int VerbForm,int VerbNum)
{
	StartVerb = GetVerbPresentSimple(VerbForm,14);
	EndVerbs += GetVerbPastParticiple(VerbNum);
}

void de::FillVerbPassivePast(int VerbForm, int VerbNum)
{
	StartVerb = GetVerbPastSimple(VerbForm,14);
	EndVerbs += GetVerbPastParticiple(VerbNum);
}

void de::FillVerbPassiveFuture(int VerbForm, int VerbNum)
{
	StartVerb = GetVerbPresentSimple(VerbForm,14);
	EndVerbs += GetVerbPastParticiple(VerbNum);
	EndVerbs += " " + GetVerbPresentSimple(0,14);
}

void de::FillVerbs(Noun& Subject, int VerbNum)
{
	
	//Wenn das Verb kein Verb ist, gehe zürück jetzt, um kein Unfall zu machen.
	if (VerbNum == 0) return;
	
	//Zuerst müssen wir die VerbForm rechnen.
	
	//Standardmäßig, nutze die "es" VerbForm.
	int VerbForm = 5;
	
	//Wenn das Subjekt ein Pronomen ist, die VerbForm ist die Nummer des Pronomens
	if (Subject.ID < 10 && Subject.ID > 0) VerbForm = Subject.ID;
	//Wenn es mehr als ein Subjekt gibt, oder das Subjekt Plural ist, nutze die VerbForm des Plurals.
	if (NumFilledSubjects > 0 || Subject.IsPlural) VerbForm = 8;
	//Wenn es kein Subjekt gibt, nutzte die Infinitivverbform.
	if (NumFilledSubjects < 0) VerbForm = 0;
	
	if (st < 2)
	{
		StartVerb = GetVerbPresentSimple(VerbForm,VerbNum);
	}
	else if (st < 10)
	{
		if (VerbNum < 3)
			StartVerb = GetVerbPastSimple(VerbForm,VerbNum);
		else
			FillVerbPastPerfekt(VerbForm,VerbNum);
	}
	else if (st < 14)
	{
		FillVerbFuture(VerbForm,VerbNum);
	}
	else if (st < 16)
	{
		FillVerbFuturePerfekt(VerbForm,VerbNum);
	}
	else if (st < 18)
	{
		FillVerbPassivePresent(VerbForm,VerbNum);
	}
	else if (st < 26)
	{
		FillVerbPassivePast(VerbForm,VerbNum);
	}
	else if (st < 32)
	{
		FillVerbPassiveFuture(VerbForm,VerbNum);
	}
	
}