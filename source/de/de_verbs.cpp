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
	
	is.close();
	return "";
	
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
	
	StartVerb = GetVerbPresentSimple(VerbForm,VerbNum);
	
}