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
   lang->sadj[sub][subadj]=getInt();
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
void Parser::_parseObject(Language* lang){
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
   lang->o[obj]=*n;
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("adj")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->oadj[obj][objadj]=getInt();
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("it")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int i = getInt();
   noun* n=lang->getIt(i);
   lang->o[obj]=*n;
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
 lang->onum=obj;
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
   _parseObject(lang);
  }
  else if (rstLook() && check("adjprepos1")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   lang->addPreposAdj1(getInt());
   expect(')',__FILE__,__LINE__);
  }
  else if (rstLook() && check("idobj")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   noun* n=parseNoun();
   lang->setIndirectObject(n);
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
  else if (rstLook() && check("prepos1")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int prepos = getInt();
   expect(',',__FILE__,__LINE__);
   noun* n=parseNoun();
   expect(')',__FILE__,__LINE__);
   lang->setPreposObj1(prepos,n);
  }
  else if (rstLook() && check("prepos2")){
   rstPtr();
   expect('(',__FILE__,__LINE__);
   int prepos = getInt();
   expect(',',__FILE__,__LINE__);
   noun* n=parseNoun();
   expect(')',__FILE__,__LINE__);
   lang->setPreposObj2(prepos,n);
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
  else if (rstLook() && check("st")){
   rstPtr();
   expect(' ',__FILE__,__LINE__);
   lang->setSentenceType(getInt());
   expect(' ',__FILE__,__LINE__);
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
