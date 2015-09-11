#include "../Language.h"
#pragma once
#include <string>
#include <fstream>
class en: public Language{
	public:
		std::string createSentence();
	private:

		//Nouns
		std::string GetNoun(noun* Noun,bool ObjCase);
		std::string GetNounString(noun* Noun,bool ObjCase);

		//Articles
		std::string GetArticle(noun* Noun,bool NextLetterIsVowel);

		//Numerals
		std::string GetNumeral(noun* Noun,bool ForceN);

		//Verbs
		std::string GetVerb(noun& Noun, int snum, int VerbNum, int SentenceType);
		std::string GetVerbSimplePresent(int VerbForm, int VerbNum);
		std::string GetVerbPreAdd(int VerbNum);
		std::string GetVerbPresentProgressive(int VerbForm, int VerbNum);

		//General Boilerplate
		bool IsVowel(char Letter);
		bool GotoLine(std::ifstream& File,int Line);
		bool GotoSegment(std::ifstream& File, int Segment);
		std::string GetSegment(std::ifstream& File);
		void ParseVerb(int Verb, int N);
};
