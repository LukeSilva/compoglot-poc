#include "../settings.h"
#include "../Language.h"
#pragma once
#include <string>
#include <fstream>

class de : public Language 
{
	private:
		//Boilerplate
		bool GotoSegment(std::ifstream& is, int Segment);
    bool GotoLine(std::ifstream& is, int Line);
    std::string GetSegment(std::ifstream& File);
		
		std::string GetNounString(Noun& n);
    std::string GetNoun(Noun& n, int Case);
	public:
    std::string createSentence();
};
