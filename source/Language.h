#pragma once
#include <string>
class Language;
typedef struct noun{
 int id;
 int num;
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
 int typ;
 bool plural;
 bool reflex;
 bool usegenitive;
 noun* genitivenoun;
 int prepos;
 // sixteen adjectives per noun
 int adj[16];
 Language* rClause;
 bool useRClause;
 int rClauseObj;
 bool rClauseEssential;
 int data;
}noun;

#include "settings.h"
void clearNoun(noun* n);
class Language{
protected:
 char* buf[NUM_BUF];
 int v1;
 int v2;
 int v3;
 int adverbs[NUM_ADVERBS];
 int st;
 char * sentence;
public:
 bool punctuation;
 int question;
 //List of subjects
 noun s[16];
 //Number of filled subjects.
 int snum;
 //List of objects
 noun obj[8][16];
 //Number of filled objects
 int objnum[8];
 //conjunction type between objects (and / or)
 int octype[8];
 //conjunction type between subjects (and / or)
 int sctype;
 int data;
 bool neg;
 Language* subClause;
 int verb1;
 int verb2;
 int conjunction;
 bool clause;
 void newSentence();
 void addAdverb(int adverbId);
 void setVerb1(int verbId);
 void setVerb2(int verbId);
 void setVerb3(int verbId);
 virtual std::string createSentence();
 virtual std::string createSubClause();
 virtual noun * getIt(int id);
 void setSentenceType(int sentenceType);
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
