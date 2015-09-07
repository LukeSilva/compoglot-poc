#include "../Language.h"
#pragma once
#include <string>
#include <fstream>
class en: public Language{
	public:
		std::string createSentence();
	private:
		std::string GetNoun(noun* Noun,bool ObjCase);
		std::string GetNounString(noun* Noun,bool ObjCase);

		std::string GetArticle(noun* Noun,bool NextLetterIsVowel);

		std::string GetNumeral(noun* Noun,bool ForceN);

		bool IsVowel(char Letter);
		bool GotoLine(std::ifstream& File,int Line);
		bool GotoSegment(std::ifstream& File, int Segment);
		std::string GetSegment(std::ifstream& File);
};
