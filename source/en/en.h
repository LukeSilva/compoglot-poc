#include "../Language.h"
#include <stdio.h>
class en_en: public Language{
 public:
  char * createSentence();
 char lang[3];
 char* buf[256];
 char* QuestionVerb1;
 private:
 
  bool isVowel(char c);
  void gotoline(FILE* rFile, int line);
  char* getSentenceNormal();
  char* getQuestionSentence();
  //Prepositions
  char* getPrepos(int prepos);
  int getPreposLength(int prepos);
  //Nouns
  char* getNoun(int s,int form);
  int getNounLength(int s,int form);
  char getNounType(int s);
  int getNewNoun(int s);

  //Verbs
  char* getOtherVerb(int v1,int v2);
  char* getVerbPreAdd(int v);
  char* getVerbPresent(int v,int f,int s,int st,char* midadverb);
  char* getVerbPast(int v,int f, int s,bool dr,char* midadverb);
  char* getVerbPastProgressive(int v,int f,int s,int st,char* midadverb);
  char* getVerbPast(int v,int f,int s,int st,char* midadverb);
  char* getVerb(int v, int f,int s, int st,char* midadverb);
  int getVerbLength(int v,int f,int s,int st,char* midadverb);
  int getVerbFormFromSubjectType(int t,int s);
  char getVerbType(int v, int st);
  int hasform(int s,int form);
  //Adjective
  char* getAdjective(int adj);
  int getAdjectiveLength(int adj);
  //Article
  char* getNumberAsString(int number);
  int getArticleLength(int s, int form,int num,int typ);
  char* getArticle(int s, int form,int num,int typ);
  //Adverbs
  char* getAdverb(int adverbId);
  char getAdverbType(int adverbId);
  char* getMiddleAdverbs(int* adverbs);
  char* getEndAdverbs(int* adverbs);
  char* getStartAdverbs(int* adverbs);
  int getEndAdverbsLength(int* adverbs);
  char* getConjunction(int conjunction);
  char* getSubClause(int conjunction,Language* subClause);
  void parseVerb(int v,int n);
};
