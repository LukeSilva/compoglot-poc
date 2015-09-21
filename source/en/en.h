#include "../settings.h"
#include "../Language.h"
#pragma once
#include <string>
#include <fstream>
class en: public Language{
	public:
		std::string createSentence();
	private:

		//Definitions (these are set in en.cpp)
		static const std::string FutureTenseMarker; // = "will"
		static const std::string GenitiveMarker; // = "of"
		static const std::string RClausePersonalMarker; // = "who"
		static const std::string RClauseEssentialMarker; // = "that"
		static const std::string RClauseNonEssentialMarker; // = "which"
		static const std::string QuestionMarkers[6]; // = {"who ","what ","when ","where ","why ","how "};


		//Nouns
		std::string GetNoun(noun* Noun,bool ObjCase);
		std::string GetNounString(noun* Noun,bool ObjCase);
		int GetNounType(int NounNum);

		//Articles
		std::string GetArticle(noun* Noun,bool NextLetterIsVowel);

		//Numerals
		std::string GetNumeral(noun* Noun,bool ForceN);

		//Verbs
		std::string GetOtherVerb(int VerbNum1, int VerbNum2);
		std::string GetVerb(noun& Noun, int snum, int VerbNum, int SentenceType);
		std::string GetVerbPresentSimple(int VerbForm, int VerbNum, bool IgnoreNeg = false, bool HelperVerb = false);
		std::string GetVerbPreAdd(int VerbNum);
		std::string GetVerbPresentProgressive(int VerbForm, int VerbNum, bool IgnoreNeg = false);
		std::string GetVerbPastSimple(int VerbForm, int VerbNum, bool Perfect = false, bool IgnoreNeg = false, bool HelperVerb = false);
		std::string GetVerbPastProgressive(int VerbForm, int VerbNum, bool IgnoreNeg = false);
		std::string GetVerbPastPerfect(int VerbForm, int VerbNum, bool IgnoreNeg = false);
		std::string GetVerbPastPerfectProgressive(int VerbForm, int VerbNum, bool IgnoreNeg = false);
		std::string GetVerbFutureSimple(int VerbForm, int VerbNum, bool IgnoreNeg = false);
		std::string GetVerbFutureProgressive(int VerbForm,int VerbNum, bool IgnoreNeg = false);
		std::string GetVerbFuturePast(int VerbForm, int VerbNum, bool IgnoreNeg = false);
		std::string GetVerbFuturePastProgressive(int VerbForm, int VerbNum, bool IgnoreNeg = false);

		//Passive Verbs
		std::string GetVerbPassivePresentProgressive(int VerbForm, int VerbNum);
		std::string GetVerbPassivePresentSimple(int VerbForm, int VerbNum);
		std::string GetVerbPassivePastSimple(int VerbForm, int VerbNum);
		std::string GetVerbPassivePastProgressive(int VerbForm, int VerbNum);
		std::string GetVerbPassivePastPerfect(int VerbForm, int VerbNum);
		std::string GetVerbPassivePastPerfectProgressive(int VerbForm, int VerbNum);
		std::string GetVerbPassiveFutureSimple(int VerbForm, int VerbNum);
		std::string GetVerbPassiveFutureProgressive(int VerbForm, int VerbNum);
		std::string GetVerbPassiveFuturePast(int VerbForm, int VerbNum);
		std::string GetVerbPassiveFuturePastProgressive(int VerbForm, int VerbNum);

		//Prepositions
		std::string GetPrepos(int PreposNum);

		//Adjectives
		std::string GetAdjective(int AdjectiveNum);

		//Conjunctions/Subclauses
		std::string GetSubClause();
		std::string GetConjunction(int ConjunctionNum);

		//General Boilerplate
		bool IsVowel(char Letter);
		bool GotoLine(std::ifstream& File,int Line);
		bool GotoSegment(std::ifstream& File, int Segment);
		std::string GetSegment(std::ifstream& File);
		void ParseVerb(int Verb, int N);
};
