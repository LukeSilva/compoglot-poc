#include "parser.h"
#include <stdio.h>
#include "../settings.h"
#include "../Language.h"
void Parser::_parseSubject(Language* lang){
 int sub=0;
 int subadj=0;
 while (rstLook() && string[lookptr]!=')'){
  if (rstLook() && LookAHead()==0){
   error("Premature end of string",__FILE__,__LINE__);
  }
  else if (rstLook() && check("n")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   noun* n=parseNoun();
   lang->s[sub]=*n;
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("adj")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->s[sub].adj[subadj]=getInt();
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("it")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int i = getInt();
   noun* n=lang->getIt(i);
   lang->s[sub]=*n;
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check(",")){
   rstPtr();
   sub++;
   subadj=0;
  }
  else{
   error("Unkown Token!",__FILE__,__LINE__);
  }
 }
 LookAHead();
 rstPtr();
 lang->snum=sub;
}
void Parser::__parseObject(Language* lang,int objid){
 int obj=0;
 int objadj=0;
 while (rstLook() && string[lookptr]!=')'){
  if (rstLook() && LookAHead()==0){
   error("Premature end of string",__FILE__,__LINE__);
  }
  else if (rstLook() && check("n")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   noun* n=parseNoun();
   lang->obj[objid][obj]=*n;
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("adj")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   if (lang->obj[objid][obj].id == 0)
   {
	   lang->obj[objid][obj].id = 14;
   }
   lang->obj[objid][obj].adj[objadj]=getInt();
   expect(')',__FILE__,__LINE__);
   objadj++;
  }
  else if (rstLook() && check("it")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int i = getInt();
   noun* n=lang->getIt(i);
   lang->obj[objid][obj]=*n;
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check(",")){
   rstPtr();
   obj++;
   objadj=0;
  }
  else{
   
   error("Unkown Token!",__FILE__,__LINE__);
  }
 }
 LookAHead();
 rstPtr();
 lang->objnum[objid]=obj;
}

void Parser::__parseObjects(Language* lang){
  while (rstLook() && string[lookptr]!=')'){
   if (rstLook() && LookAHead()==0){
    error("premature end of string",__FILE__,__LINE__);
   }
   else{
    int i = getInt();
    if (i > 0 && i < 9){
     i=i-1;
     expect('(',__FILE__,__LINE__);
     __parseObject(lang,i);
    }else{
     error("object identifier was out of range",__FILE__,__LINE__);
    }
   }
  }	
 LookAHead();
 rstPtr();
}
void Parser::_parse(Language* lang){
 while (rstLook() && string[lookptr]!=')')
 {
  if (rstLook() && LookAHead()==0){
   error("Premature end of string",__FILE__,__LINE__);
  }
  else if (rstLook() && check("sub")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   _parseSubject(lang);
  }
  else if (rstLook() && check("obj")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   __parseObjects(lang);	
  }
  else if (rstLook() && check("adjprepos1")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->addPreposAdj1(getInt());
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("oprepos")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int id = getInt() - 1;
   if (id < 0 || id > 7)
   {
    error("Invalid id for oprepos()",__FILE__,__LINE__);
   }
   expect(',',__FILE__,__LINE__);
   int prepos = getInt();
   for (int i = 0; i < 16; ++i)
   {
    lang->obj[id][i].prepos = prepos;
   }
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("datao")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int id = getInt() - 1;
   if (id < 0 || id > 7)
   {
    error("Invalid id for datao()",__FILE__,__LINE__);
   }
   expect(',',__FILE__,__LINE__);
   int data = getInt();
   for (int i = 0; i  < 16; ++i)
   {
    lang->obj[id][i].data=data;
   }
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("octype"))
  {
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int id = getInt() - 1;
   if (id < 0 || id > 7 )
   {
    error("Invalid id for octype()",__FILE__,__LINE__);
   }
   expect(',',__FILE__,__LINE__);
   int ctype = getInt();
   lang->octype[id] = ctype;
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("datas")){
   expect('(',__FILE__,__LINE__);
   int data = getInt();
   for (int i = 0; i < 16; ++i)
   {
    lang->s[i].data=data;
   }
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("sctype")){
   expect('(',__FILE__,__LINE__);
   int data = getInt();
   lang->sctype=data;
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("Verb1")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->verb1=getInt();
   expect(')',__FILE__,__LINE__);
  } 
  else if (rstLook() && check("Verb2")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->verb2=getInt();
   expect(')',__FILE__,__LINE__);
  } 
  else if (rstLook() && check("Verb")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   if (verb==0) lang->setVerb1(getInt());
   else lang->setVerb2(getInt());
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("v1")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->setVerb1(getInt());
   expect(')',__FILE__,__LINE__);
  }  
  else if (rstLook() && check("v2")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->setVerb2(getInt());
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("adverb")){
   rstPtr(); 
   expect('(',__FILE__,__LINE__);
   lang->addAdverb(getInt());
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("fprepos")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int prepos = getInt();
   expect(',',__FILE__,__LINE__);
   noun* n=parseNoun();
   expect(')',__FILE__,__LINE__);
   lang->setFrontPreposObj(prepos,n);
  }
  else if (rstLook() && check("neg ")){
   rstPtr();
   lang->neg=!lang->neg;
  }
  else if (rstLook() && check("clause")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int conj = getInt();
   expect(',',__FILE__,__LINE__);
   Language* nlang = getLanguageFromStringId(langid);
   nlang->newSentence();
   _parse(nlang);
   lang->conjunction = conj;
   lang->subClause=nlang;
  }
  else if (rstLook() && check("question")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->question=getInt();
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("st")){
   rstPtr();
   expect(' ',__FILE__,__LINE__);
   lang->setSentenceType(getInt());
   expect(' ',__FILE__,__LINE__);
  }
  else if (rstLook() && check("punc")){
   rstPtr();
   expect(' ',__FILE__,__LINE__);
   lang->punctuation = getInt();
   expect(' ',__FILE__,__LINE__);
  }
  else if (rstLook() && check("o")){
   error("Using the o tag is depreciated!",__FILE__,__LINE__);
  }

  else{
   error("Unknown Token",__FILE__,__LINE__);
  }
 } 
}
char* Parser::parse(char* _langid,char* in){
 //Setup internals
 ptr=0;
 lookptr=0;
 string=in;
 look=in[lookptr];
 Language* lang;
 langid=_langid;
 //default Verb(x) to v1(x)
 verb=0;

 //Create the language class form the langid
 lang = getLanguageFromStringId(langid);
 lang->newSentence();
 //Setup progressive present tense for default
 lang->setSentenceType(1);

 //Expect an opening clause
 expect('(',__FILE__,__LINE__);
 //Now do the parsing on lang
 _parse(lang);
 return lang->createSentence();
}
