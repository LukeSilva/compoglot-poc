#include "../settings.h"
#include "../Language.h"
#pragma once
#include <string>
#include <fstream>

class de : public Language 
{
	private:
		//Strings
		static const std::string Und;
		static const std::string Oder;
		static const std::string Articles[14][4][4];
		static const std::string Numerals[12];
		static const std::string AdjectiveEndings[3][4][4];
		static const std::string QuestionMarkers[6];
		
		
		//Boilerplate
		bool GotoSegment(std::ifstream& is, int Segment);
		bool GotoLine(std::ifstream& is, int Line);
		std::string GetSegment(std::ifstream& File);
		void ParseVerb(int verb,int n);
		Noun * getIt(int id);		

		//Numerals
		std::string GetNumeral(Noun& n);
		
		//Nouns
		std::string GetNounString(Noun& n);
		std::string GetNoun(Noun& n, int Case);
		int GetNounType(Noun& n);
		
		//Articles
		std::string GetArticle(Noun& n);
	
		//Prepositions
		std::string GetPrepos(Noun& n);
		
		//Adjectives
		std::string GetAdjective(Noun& n, int AdjectiveNum);
		
		//Verbs
		std::string GetVerbPresentSimple(int VerbForm, int VerbNum);
		std::string GetVerbPastParticiple(int VerbNum);
		std::string GetVerbPastSimple(int VerbForm, int VerbNum);
		void FillVerbFuture(int VerbForm, int VerbNum);
		void FillVerbFuturePerfekt(int VerbForm, int VerbNum);
		void FillVerbPastPerfekt(int VerbForm, int VerbNum);
		void FillVerbPassivePresent(int VerbForm,int VerbNum);
		void FillVerbPassivePast(int VerbForm, int VerbNum);
		void FillVerbPassiveFuture(int VerbForm, int VerbNum);
		void FillVerbs(Noun& Subject, int VerbNum);
		
		//SubClauses
		std::string GetSubClause();
		
		std::string StartVerb;
		std::string EndVerbs;
		
	public:
    std::string createSentence();
};
