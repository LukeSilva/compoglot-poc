#include "Language.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

Noun::Noun()
{
	ID = 0;
	Data = 0;
	Numeral = 0;
	GenitiveNoun = NULL;
	IsPlural = false;
	PreposNum = 0;
	RelativeClause = NULL;
	IsRelativeClauseEssential = false;
	RelativeClauseObj = 0;
	IsReflexive = false;
	ArticleType = 0;
	ShouldUseGenitive = false;
	ShouldUseRelativeClause = false;
	for (int i = 0; i < 16; ++i)
	{
		Adjectives[i] = 0;
	}
}
Noun::~Noun()
{
}




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
Noun* Language::getIt(int id){
	Noun * n = new Noun;
	n->ID=5;
	n->Numeral=0;
	n->IsPlural=false;
	n->IsReflexive=false;
	n->ShouldUseRelativeClause=false;
	n->ShouldUseGenitive=false;
	n->ArticleType=0;
	for (int i = 0; i < 16; ++i)
	{
		n->Adjectives[i]=0;
	}
	return n;
}
void clearNoun(Noun* n)
{

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
	for (int i = 0; i < 8; ++i)
	{  
		ObjConjunctionType[i] = 0;
		NumFilledObjects[i] = -1;
	}
	for (int i=0;i<NUM_ADVERBS;i++)
		adverbs[i]=0;
}
