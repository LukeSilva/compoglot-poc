#include "en.h"
#include "../settings.h"
#include "../parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char en_en_question_words[6][20]={"who ","what ","when ","where ","why ","how "};
void en_en_gotoline(FILE* rFile, int line){
 int linenum = 1;
 while (linenum<line){
  if (fgetc(rFile)=='\n')
   linenum++;
  if (feof(rFile)){
   return;
  }
 }
}
int en_en::getVerbFormFromSubjectType(int t,int s){
 if (t=='n' || t=='o' || t=='p' || t=='b') return 5;
 else if (t=='m') return 3;
 else if (t=='f') return 4;
 else if (t=='d' && s<10) return s;
 else if (t=='d' || t=='e') return 5;
 return 0;
}
char en_en::getVerbType(int v,int st){
 FILE* rFile;
 rFile = fopen(DICTIONARY EN_EN_FOLDER "verb_present","r");
 gotoline(rFile,v);
 char t=fgetc(rFile);
 fclose(rFile);
 return t;
}
bool en_en_isVowel(char c)
{
 if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u') return true;
 return false;
}




void en_en::gotoline(FILE* rFile, int line){
 int linenum = 1;
 while (linenum<line){
  if (fgetc(rFile)=='\n')
   linenum++;
  if (feof(rFile)){
   return;
  }
 }
}

bool en_en::isVowel(char c)
{
 if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u') return true;
 return false;
}
char* en_en::getNounString(noun* n,int vr,int vnr)
{
  char* buffer;
  buffer = (char*) malloc(BUFFER_SIZE*10);
  buffer[0] = 0;
  strcat(buffer,getArticle(n->id,n->plural?4:n->reflex?vr:vnr, n->num,n->typ));
  for (int i=0;i<16;i++)
  {
   if (n->adj[i]!=0)
   {
    strcat(buffer,getAdjective(n->adj[i]));
   }
  }
  strcat(buffer,getNoun(n->id,n->plural?4:n->reflex?vr:vnr));
  if (n->usegenitive)
  {
    strcat(buffer,EN_EN_OF);
    strcat(buffer,getNounString(n->genitivenoun,vr,vnr));
  }
  return buffer;
}
char* en_en::getSentenceNormal(){
 int a=0;
 char debug='a';
 bool splural=(snum>0) | s[0].plural;

  buf[a++]=getStartAdverbs(&adverbs[0]);
 if(prepos_prepos[2]!=0){
  buf[a++]=getPrepos(prepos_prepos[2]);
  buf[a++]=getArticle(prepos_object[2].id,prepos_object[2].plural?4:prepos_object[2].reflex?3:2,prepos_object[2].num,prepos_object[2].typ);
  buf[a++]=getNoun(prepos_object[2].id,prepos_object[2].plural?4:prepos_object[2].reflex?3:2);
 } 
 for (int sc=0;sc<16;sc++){
  if (s[sc].id!=0){
   if (sc > 0) buf[a++]=", ";
   if (sc == snum && snum>0) buf[a++]=EN_EN_ANDNOUN;
   buf[a++]=getNounString(&s[sc],0,0);
  }
 }
 if (v1!=0)
  buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st,getMiddleAdverbs(&adverbs[0]));
 if (v2!=0)
  buf[a++]=getOtherVerb(v1,v2);
 for (int objid=0;objid<8;objid++)
 {
  for (int oc=0;oc<16;oc++){
   if (obj[objid][oc].id!=0){
    if (oc > 0) buf[a++]=", ";
    if (oc == objnum[objid] && objnum[objid]>0) buf[a++]=EN_EN_ANDNOUN;
    buf[a++]=getNounString(&obj[objid][oc],3,1);
   }
  }
 } 
 buf[a++]=getEndAdverbs(&adverbs[0]);

 if(subClause!=NULL && conjunction!=0){
  buf[a++]=getSubClause(conjunction,subClause);
 }

 int sl=0;
 for (int i=0;i<256;i++){
  if(buf[i]!=NULL)
   sl+=strlen(buf[i]);
 }
 char* buffer = (char*)calloc(sl+4,sizeof(char));
 for (int i=0;i<256;i++){
  if(buf[i]!=NULL)
  {
   strcat(buffer,buf[i]);
  }
 }
 if (clause==false){
  char* buf2 = buffer;
  buffer = (char*) calloc(strlen(buf2)+2,sizeof(char));
  int len = strlen(buf2);
  int i=1;
  int j=1;
  char c;
  c = buf2[0];
  if (c >= 'a' && c <= 'z')
   buffer[0]=c-32;
  else buffer[0]=c;
  while (i<len){
   if (buf2[i]!=' '){
    buffer[j++]=buf2[i++];
   }else if (buf2[i+1]==','){
    buffer[j++]=',';
    i=i+2;
   }else if (buf2[i+1]==0){
    buffer[j++]='.';
    i++;
   }else buffer[j++]=buf2[i++];
  }
 }
 return buffer;
}
char * en_en::getQuestionSentence(){
 int a=0;
 char debug='a';
 bool splural=(snum>0) | s[0].plural;
 bool doQuestion = st>0 && st < 4;
 bool doVerb1=true;
 if (question > 1)
 {
  buf[a++]=&en_en_question_words[question-2][0];
 } 
 if (doQuestion){
  //Add helper verb at front of sentence
  if (v2==0 && v1!=1){
   //Do is our helper verb
   buf[a++]=getVerb(68,-1,splural?8:s[0].id,st,"");
  }else if (v1!=0){
   buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st,getMiddleAdverbs(&adverbs[0]));
   doVerb1 = false;
  }
 }else {
  //As question is set, this call should only return the helper verb.
  buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st,getMiddleAdverbs(&adverbs[0]));
  doVerb1=false;
 }
 
 for (int sc=0;sc<16;sc++){
  if (s[sc].id!=0){
   if (sc > 0) buf[a++]=", ";
   if (sc == snum && snum>0) buf[a++]=EN_EN_ANDNOUN;
   buf[a++]=getArticle(s[sc].id,s[sc].plural ? 4:0, s[sc].num,s[sc].typ);
   for (int i=0;i<16;i++)
   {
    if (s[sc].adj[i]!=0)
    {
     buf[a++]=getAdjective(s[sc].adj[i]);
    }
   }
   buf[a++]=getNoun(s[sc].id,s[sc].plural ?4:0);
  }
 }
  buf[a++]=getStartAdverbs(&adverbs[0]);
 if (v1!=0 && doVerb1)
  buf[a++]=getVerb(v1,-1,1,1,getMiddleAdverbs(&adverbs[0]));
 else if (v1!=0 && doQuestion == false)
  buf[a++]=QuestionVerb1;
 if (v2!=0)
  buf[a++]=getOtherVerb(v1,v2);
 if (idobj.id!=0){
  buf[a++]=getArticle(idobj.id,idobj.plural?4:idobj.reflex?3:2,idobj.num,idobj.typ);
  buf[a++]=getNoun(idobj.id,idobj.plural?4:idobj.reflex?3:2);
 }
 for (int objid=0;objid<8;objid++)
 {
  if (objprepos[objid]!=0)
   buf[a++]=getPrepos(objprepos[objid]);
  for (int oc=0;oc<16;oc++){
   if (obj[objid][oc].id!=0){
    if (oc > 0) buf[a++]=", ";
    if (oc == objnum[objid] && objnum[objid]>0) buf[a++]=EN_EN_ANDNOUN;
     buf[a++]=getArticle(obj[objid][oc].id,obj[objid][oc].plural?4:obj[objid][oc].reflex?3:1,obj[objid][oc].num,obj[objid][oc].typ);
   }
   for (int i=0;i<16;i++)
   {
      if (objadj[objid][oc][i]!=0)
     {
      buf[a++]=getAdjective(objadj[objid][oc][i]);
     }
   } 
   if (obj[objid][oc].id!=0)
    buf[a++]=getNoun(obj[objid][oc].id,obj[objid][oc].plural?4:obj[objid][oc].reflex?3:1);
  }
 } 
 //Prepositions goes here
 /*if(prepos_prepos[0]!=0){
  buf[a++]=getPrepos(prepos_prepos[0]);
  buf[a++]=getArticle(prepos_object[0].id,prepos_object[0].plural?4:prepos_object[0].reflex?3:2,prepos_object[0].num,prepos_object[0].typ);
  for (int i=0;i<16;i++)
  {
   if (prepos_adj[0][i]!=0)
   {
    buf[a++]=getAdjective(prepos_adj[0][i]);
   }
  }
  buf[a++]=getNoun(prepos_object[0].id,prepos_object[0].plural?4:prepos_object[0].reflex?3:2);

 } 
 if(prepos_prepos[1]!=0){
  buf[a++]=getPrepos(prepos_prepos[1]);
  buf[a++]=getArticle(prepos_object[1].id,prepos_object[1].plural?4:prepos_object[1].reflex?3:2,prepos_object[1].num,prepos_object[1].typ);
  buf[a++]=getNoun(prepos_object[1].id,prepos_object[1].plural?4:prepos_object[1].reflex?3:2);
 }*/ 
 if(prepos_prepos[2]!=0){
  buf[a++]=getPrepos(prepos_prepos[2]);
  buf[a++]=getArticle(prepos_object[2].id,prepos_object[2].plural?4:prepos_object[2].reflex?3:2,prepos_object[2].num,prepos_object[2].typ);
  buf[a++]=getNoun(prepos_object[2].id,prepos_object[2].plural?4:prepos_object[2].reflex?3:2);
 } 
 buf[a++]=getEndAdverbs(&adverbs[0]);

 if(subClause!=NULL && conjunction!=0){
  buf[a++]=getSubClause(conjunction,subClause);
 }

 int sl=0;
 for (int i=0;i<256;i++){
  if(buf[i]!=NULL)
   sl+=strlen(buf[i]);
 }
 char* buffer = (char*)calloc(sl+4,sizeof(char));
 for (int i=0;i<256;i++){
  if(buf[i]!=NULL)
  {
   strcat(buffer,buf[i]);
  }
 }
 if (clause==false){
  char* buf2 = buffer;
  buffer = (char*) calloc(strlen(buf2)+2,sizeof(char));
  int len = strlen(buf2);
  int i=1;
  int j=1;
  char c;
  c = buf2[0];
  if (c >= 'a' && c <= 'z')
   buffer[0]=c-32;
  else buffer[0]=c;
  while (i<len){
   if (buf2[i]!=' '){
    buffer[j++]=buf2[i++];
   }else if (buf2[i+1]==','){
    buffer[j++]=',';
    i=i+2;
   }else if (buf2[i+1]==0){
    buffer[j++]='?';
    i++;
   }else buffer[j++]=buf2[i++];
  }
 }
 return buffer;
}
char * en_en::createSentence(){
 if(verb1!=0){
  parseVerb(0,verb1);
  verb1=0;
 }
 if (verb2!=0){
  parseVerb(1,verb2);
  verb2=0;
 }
 if (question == 0) return getSentenceNormal();
 else if (question < 8) return getQuestionSentence();
 else exit(-1);
}
