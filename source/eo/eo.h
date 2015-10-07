#include "../settings.h"
#include "../Language.h"
#pragma once
#include <string>
#include <fstream>

class eo : public Language
{
private:
		const static std::string And;
		const static std::string Or;
		
    bool GotoLine(std::ifstream& is, int Line);
    std::string GetSegment(std::ifstream& File);
		void ParseVerb(int verb,int n);
		
		std::string GetNoun(Noun& n, bool Accusative);
public:
		std::string createSentence();
};