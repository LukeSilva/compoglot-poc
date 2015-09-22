#include "Language.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

std::string Language::createSentence(){
	return "";
}
std::string Language::createSubClause(){
	return "";
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
void Language::NewSentence(){
	Capital = true;
	Punctuation = true;
	Question = 0;
	IsClause=false; 
	ExtVerb1 = 0;
	ExtVerb2 = 0;
	ExtVerb3 = 0;
	SubClause=NULL;
	Conjunction=0;
	NumFilledSubjects=-1;
	Verb1=0;
	Verb2=0;
	Verb3=0;
	st=1;
	Negate=false;
	SubConjunctionType = 0;
	for (int i=0;i<16;i++){
		clearNoun(&Subjects[i]);
	}
	for (int i = 0; i < 8; ++i)
	{  
		ObjConjunctionType[i] = 0;
		NumFilledObjects[i] = -1;
		for (int j = 0; j < 16; ++j)
		{
			clearNoun(&Objects[i][j]);
		}
	}
	for (int i=0;i<NUM_ADVERBS;i++)
		adverbs[i]=0;
}
