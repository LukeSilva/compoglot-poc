#include "../Language.h"
#include <stdio.h>
class de: public Language{
 //Data flags:
 //data&0x1:make verb come first (conjunctions)
 public:
  std::string createSubClause();
  std::string createSentence();
 private: 
  char * endVerb;
  bool hasEndVerb;
  int verbs[3];
  noun* getIt(int s);
  char getCaseOfObject(int v,int st);
  char getPreVerb2(int v1);
  void gotoline(FILE* rFile, int line);
  char getVerbType(int v,int st);
  int getVerbFormFromSubjectType(int s,int st);
  //Article
  char* getArticle(int id,int form,int num,int cas,int typ); 
  char* _getArticle(int id,int form,int num,int cas,int typ); 
  //Prepositions
  char* getPreposObject(int prepos,noun* n,int* cas,bool* adda);
  //Nouns
  char getNounType(int n);
  char* getNoun(int n,bool pl,int cas);
  //Verbs
  char* getOtherVerb(int v1,int v2);
  char* getVerb(int v, int f, int s, int st);
  char* getVerbPresent(int v, int f, int s, int st);
  char* getVerbPerfekt(int v,int f,int s,int st);
  char* getVerbSimple(int v,int f, int s, int st);
  char* getVerbFuture(int v,int f,int s,int st);
  char* getVerbFuturePerfekt(int v,int f,int s,int st);
  char* getVerbPassivePresent(int v,int f,int s,int st);
  char* getVerbPassivePast(int v,int f,int s,int st);
  char* getVerbPassiveFuture(int v,int f,int s,int st);
  //Adjectives
  char* getAdjective(int adjective,int noun,bool plural, int typ, int cas);
  char* getConjunction(int conjunction);
  char getConjunctionType(int conjunction);
  char* getSubClause();
  //General
  void parseVerb(int v, int n);
  char* getNounString(noun* n);
};
