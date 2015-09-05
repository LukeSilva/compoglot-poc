#include "../Language.h"
#pragma once
#include <string>
#include <fstream>
class en: public Language{
	public:
		std::string createSentence();
	private:
		std::string getNoun(noun* Noun,bool ObjCase);
		std::string getNounString(noun* Noun,bool ObjCase);
		bool GotoLine(std::ifstream& File,int Line);
		bool GotoSegment(std::ifstream& File, int Segment);
		std::string GetSegment(std::ifstream& File);
};
