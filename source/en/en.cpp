#include "en.h"
#include "../settings.h"
#include "../parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char * en_en::createSentence(){
 int a=0;
 char debug='a';
 bool splural=(snum>0) | s[0].plural;
 if(verb1!=0){
  parseVerb(0,verb1);
  verb1=0;
 }
 if (verb2!=0){
  parseVerb(1,verb2);
  verb2=0;
 }
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
   buf[a++]=getArticle(s[sc].id,s[sc].plural ? 4:0, s[sc].num,s[sc].typ);
   for (int i=0;i<16;i++)
   {
    if (sadj[sc][i]!=0)
    {
     buf[a++]=getAdjective(sadj[sc][i]);
    }
   }
   buf[a++]=getNoun(s[sc].id,s[sc].plural ?4:0);
  }
 }
 if (v1!=0)
  buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st,getMiddleAdverbs(&adverbs[0]));
 if (v2!=0)
  buf[a++]=getOtherVerb(v1,v2);
 if (idobj.id!=0){
  buf[a++]=getArticle(idobj.id,idobj.plural?4:idobj.reflex?3:2,idobj.num,idobj.typ);
  buf[a++]=getNoun(idobj.id,idobj.plural?4:idobj.reflex?3:2);
 }
 for (int oc=0;oc<16;oc++){
  if (o[oc].id!=0){
   if (oc > 0) buf[a++]=", ";
   if (oc == onum && onum>0) buf[a++]=EN_EN_ANDNOUN;
   buf[a++]=getArticle(o[oc].id,o[oc].plural?4:o[oc].reflex?3:1,o[oc].num,o[oc].typ);
  }
  for (int i=0;i<16;i++)
  {
    if (oadj[oc][i]!=0)
    {
     buf[a++]=getAdjective(oadj[oc][i]);
    }
  }
  if (o[oc].id!=0)
   buf[a++]=getNoun(o[oc].id,o[oc].plural?4:o[oc].reflex?3:1);
 }
//Prepositions goes here
 if(prepos_prepos[0]!=0){
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
 return buffer;
}