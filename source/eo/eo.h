#include "../settings.h"
#include "../Language.h"
#pragma once
#include <string>
#include <fstream>

class eo : public Language
{
private:
	
	enum VerbForms
	{
		FORM_INFINITIVE = 0,
		FORM_PRESENT = 1,
		FORM_PAST = 2,
		FORM_FUTURE = 3,
		FORM_CONDITIONAL = 4,
		FORM_IMPERATIVE = 5,
		FORM_PRESENT_PASSIVE_PARTICIPLE = 6,
		FORM_PAST_PASSIVE_PARTICIPLE = 7,
		FORM_FUTURE_PASSIVE_PARTICIPLE = 8
	};	
	
	const static std::string And;
	const static std::string Or;
	const static std::string VerbEndings[9];
	const static std::string Articles[14];
	const static std::string Numerals[12];
	const static std::string GenitiveMarker;
	
	bool GotoLine(std::ifstream& is, int Line);
	std::string GetSegment(std::ifstream& File);
	void ParseVerb(int verb,int n);
	
	std::string GetVerbForm(int VerbNum ,VerbForms VerbForm);
	std::string GetVerb(int VerbNum);
	
	std::string GetNoun(Noun& n, bool Accusative);
	std::string GetNounString(Noun& n);
	
	std::string GetArticle(Noun& n);
	
	std::string GetNumeral(Noun& n, bool ForceN);
	
	std::string GetPreposition(Noun& n);
	
	std::string GetAdjective(Noun& n, int AdjectiveNum);
	
	std::string GetConjunction(int ConjunctionNum);
	std::string GetSubClause();
public:
	eo() : Language("eo") {}
	std::string createSentence();
};
