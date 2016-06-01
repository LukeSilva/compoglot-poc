#pragma once
#include <string>
#include <memory>

class Language;

class Noun
{
public:
	Noun();
	~Noun();
	int ID;
	int Numeral;
	//-2 for a
	//-1 for the
	//0 for nothing
	//1 for my
	//2 for your
	//3 for his
	//4 for her
	//5 for its
	//6 for our
	//7 for your
	//8 for their
	//9 for your
	int ArticleType;
	bool IsPlural;
	bool IsReflexive;
	bool ShouldUseGenitive;
	Noun* GenitiveNoun;
	int PreposNum;
	// sixteen adjectives per noun
	int Adjectives[16];
	std::shared_ptr<Language> RelativeClause;
	bool ShouldUseRelativeClause;
	int RelativeClauseObj;
	bool IsRelativeClauseEssential;
	int Data;
	
	void addAdjective(int adjectiveNum);
};

#include "settings.h"

class Language
{
protected:
	int adverbs[0];
	Language(std::string LangID);
public:
	std::string LangID;

	Language();
	virtual ~Language();

	int Data;
	int st;
	int Verb1;
	int Verb2;
	int Verb3;
	//List of subjects
	Noun Subjects[16];
	//List of objects
	Noun Objects[8][16];
	//Number of filled subjects.
	int NumFilledSubjects;
	//Number of filled objects
	int NumFilledObjects[8];
	//Conjunction type between objects (and / or)
	int ObjConjunctionType[8];
	//Conjunction type between subjects (and / or)
	int SubConjunctionType = 0;

	int ExtVerb1;
	int ExtVerb2;
	int ExtVerb3;
	bool Negate;
	Language* SubClause;
	bool Capital;
	int Punctuation;
	int Question;
	int Conjunction;
	bool IsClause;
	void NewSentence();
	virtual std::string createSentence();
	virtual std::string createSubClause();
	virtual Noun * getIt(int id);
};

//always use simple present

#define PRESENT 0
#define PRESENT_PROGRESSIVE 0
#define PRESENT_SIMPLE 1
#define PAST 2
#define PAST_RECENT 2
#define PAST_RECENT_FORMAL 3
#define PAST_RECENT_PROGRESSIVE 4
#define PAST_RECENT_FORMAL_PROGRESSIVE 5
#define PAST_RECENT_PROGRESSIVE_FORMAL 5
#define PAST_DISTANT 6
#define PAST_DISTANT_FORMAL 7
#define PAST_DISTANT_PROGRESSIVE 8
#define PAST_DISTANT_PROGRESSIVE_FORMAL 9
#define PAST_DISTANT_FORMAL_PROGRESSIVE 9
#define FUTURE 10
#define FUTURE_RECENT 10
#define FUTURE_RECENT_PROGRESSIVE 11
#define FUTURE_DISTANT 12
#define FUTURE_DISTANT_PROGRESSIVE 13
#define FUTURE_PAST 14
#define FUTURE_PAST_PROGRESSIVE 15
#define PASSIVE_PRESENT 16
#define PASSIVE_PRESENT_PROGRESSIVE 16
#define PASSIVE_PRESENT_SIMPLE 17
#define PASSIVE_PAST 18
#define PASSIVE_PAST_RECENT 18
#define PASSIVE_PAST_RECENT_FORMAL 19
#define PASSIVE_PAST_RECENT_PROGRESSIVE 20
#define PASSIVE_PAST_RECENT_FORMAL_PROGRESSIVE 21
#define PASSIVE_PAST_RECENT_PROGRESSIVE_FORMAL 21
#define PASSIVE_PAST_DISTANT 22
#define PASSIVE_PAST_DISTANT_FORMAL 23
#define PASSIVE_PAST_DISTANT_PROGRESSIVE 24
#define PASSIVE_PAST_DISTANT_PROGRESSIVE_FORMAL 25
#define PASSIVE_PAST_DISTANT_FORMAL_PROGRESSIVE 25
#define PASSIVE_FUTURE 26
#define PASSIVE_FUTURE_RECENT 26
#define PASSIVE_FUTURE_RECENT_PROGRESSIVE 27
#define PASSIVE_FUTURE_DISTANT 28
#define PASSIVE_FUTURE_DISTANT_PROGRESSIVE 29
#define PASSIVE_FUTURE_PAST 30
#define PASSIVE_FUTURE_PAST_PROGRESSIVE 31
#define BUTTON_TEXT 32
