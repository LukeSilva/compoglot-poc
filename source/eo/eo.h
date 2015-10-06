#include "../settings.h"
#include "../Language.h"
#pragma once
#include <string>
#include <fstream>

class eo : public Language
{
private:
    bool GotoLine(std::ifstream& is, int Line);
    std::string GetSegment(std::ifstream& File);
		void ParseVerb(int verb,int n);
public:
		std::string createSentence();
};