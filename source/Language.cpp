#include "Language.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

void Language::setVerb1(int v){
 v1=v;
}
void Language::setVerb2(int v){
 v2=v;
}
void Language::setVerb3(int v){
 v3=v;
}
std::string Language::createSentence(){
	return "";
}
std::string Language::createSubClause(){
	return "";
}
void Language::setSentenceType(int t){
 st=t;
}
void Language::addAdverb(int adverbId){
 for (int i=0;i<3;i++){
  if (adverbs[i]==0){
   adverbs[i]=adverbId;
   break;
  }
 }
}
noun* Language::getIt(int id){
  noun * n = new noun;
  n->id=5;
  n->num=0;
  n->plural=false;
  n->reflex=false;
  n->useRClause=false;
  n->usegenitive=false;
  n->typ=0;
  for (int i = 0; i < 16; ++i)
  {
    n->adj[i]=0;
  }
  return n;
}
void clearNoun(noun* n)
{
	n->id = 0;
	n->data = 0;
	n->num = 0;
	n->genitivenoun = NULL;
	n->plural = false;
	n->prepos = 0;
	n->rClause = NULL;
	n->rClauseEssential = false;
	n->rClauseObj = 0;
	n->reflex = false;
	n->typ = 0;
	n->usegenitive = false;
	n->useRClause = false;
	for (int i = 0; i < 16; ++i)
	{
		n->adj[i] = 0;
	}
}
void Language::newSentence(){
 for (int i = 0; i < NUM_BUF; ++i)
 {
  buf[i] = 0;
 }
 Capital = true;
 punctuation = true;
 question = 0;
 clause=false;
 data=0;
 verb1=0;
 verb2=0;
 subClause=NULL;
 conjunction=0;
 snum=-1;
 v1=0;
 v2=0;
 v3=0;
 st=1;
 neg=false;
 sctype = 0;
 for (int i=0;i<16;i++){
	 clearNoun(&s[i]);
 }
 for (int i = 0; i < 8; ++i)
 {  
   octype[i] = 0;
	 objnum[i] = -1;
	 for (int j = 0; j < 16; ++j)
	 {
		 clearNoun(&obj[i][j]);
	 }
 }
 for (int i=0;i<NUM_ADVERBS;i++)
  adverbs[i]=0;
}
