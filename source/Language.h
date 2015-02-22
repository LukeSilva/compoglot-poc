#ifndef LANGUAGE_H
#define LANGUAGE_H
typedef struct{
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
}noun;
class Language;
#include "settings.h"
class Language{
protected:
 int v1;
 int v2;
 int v3;
 int adverbs[NUM_ADVERBS];
 noun dobj;
 noun idobj;
 noun prepos_object[3];
 int prepos_prepos[3];
 int prepos_adj[3][16];
 int st;
 char * sentence;
public:
 int question;
 noun s[16];
 int snum;
 int sadj[16][16];
 int data_s;
 noun obj[8][16];
 int objnum[8];
 int objadj[8][16][16];
 int objprepos[8];
 int data_obj[8];
 
 //noun o[16];
 //int oadj[16][16];
 //int onum;

 int data;
 bool neg;
 Language* subClause;
 int verb1;
 int verb2;
 int conjunction;
 bool clause;
 void newSentence();
 void addAdverb(int adverbId);

 void setPreposObj1(int prepos,int object,int amount,bool plural,int typ);
 void setPreposObj1(int prepos,noun* o);
 void addPreposAdj1(int adjective);
 void setPreposObj2(int prepos,int object,int amount,bool plural,int typ);
 void setPreposObj2(int prepos,noun* o);
 void setFrontPreposObj(int prepos,int object,int amount,bool plural,int typ);
 void setFrontPreposObj(int prepos,noun* o);

 void setVerb1(int verbId);
 void setVerb2(int verbId);

 void setVerb3(int verbId);


 void setDirectObject(int objectId,int amount,bool plural,bool reflexive,int typ);

 void setIndirectObject(int objectId,int amount,bool plural,bool reflexive,int typ);
 void setIndirectObject(noun* _idobj);
 virtual char * createSentence();
 virtual char * createSubClause();
 virtual noun * getIt(int id);
 void setSentenceType(int sentenceType);

 
};

//always use simple present
#define PRESENT_SIMPLE 1
//prefer progressive tense, but fall back to simple when not possible
#define PRESENT 0
//prefer 
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

#endif
