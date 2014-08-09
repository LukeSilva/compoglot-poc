#include "de.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char a[2]="";
char de_nicht[7]="nicht ";
char de_zu[4]="zu ";
char de::getVerbType(int v,int st){
 FILE* rFile;
 if (st<2){
  rFile = fopen(DICTIONARY DE_FOLDER "verb_present","r");
 }
 gotoline(rFile,v);
 char t=fgetc(rFile);
 fclose(rFile);
 return t;
}

int de::getVerbFormFromSubjectType(int s,int st)
{
 if (st=='P' && s < 11) return s;
 else if (st=='m') return 3;
 else if (st=='f') return 4;
 else if (st=='n') return 5;
 return 5;
}
noun* de::getIt(int id){
  FILE * rFile = fopen(DICTIONARY DE_FOLDER "nouns" , "r");
  gotoline(rFile,id);
  char st = fgetc(rFile);
  fclose(rFile);
  noun * n = new noun;
  n->id=getVerbFormFromSubjectType(id,st);
  n->num=0;
  n->plural=false;
  n->reflex=false;
  n->typ=0;
  return n;
}
void de::gotoline(FILE* rFile, int line){
 int linenum = 1;
 while (linenum<line){
  if (fgetc(rFile)=='\n')
   linenum++;
  if (feof(rFile)){
   return;
  }
 }
}

char de::getCaseOfObject(int v,int st){
 FILE* rFile;
 if (st<10){
  rFile=fopen(DICTIONARY DE_FOLDER "verb_present","r");
 }
 gotoline(rFile,verbs[v]);
 fgetc(rFile);
 char t=fgetc(rFile);
 t-='0';
 fclose(rFile);
 if (t==4) t = getCaseOfObject(v+1,st);
 return t;
}
char de::getPreVerb2(int v1){
 FILE* rFile;
 rFile=fopen(DICTIONARY DE_FOLDER "verb_present","r");
 gotoline(rFile,v1);
 fgetc(rFile);
 fgetc(rFile);
 char t = fgetc(rFile);
 t-='0';
 fclose(rFile);
 return t;
}
char* de::createSubClause(){
 if(verb1!=0){
  parseVerb(0,verb1);
  verb1=0;
 }
 if (verb2!=0){
  parseVerb(1,verb2);
  verb2=0;
 }
 int a=0;
 hasEndVerb=false;
 verbs[0]=v1;
 verbs[1]=v2;
 verbs[2]=v3;
 bool splural=(snum>0) | s[0].plural;
 if (prepos_prepos[2]!=0){
  buf[a++]=getPreposObject(prepos_prepos[2],prepos_object[2].id,prepos_object[2].num,prepos_object[2].plural,prepos_object[2].typ);
 }
 for(int sc=0;sc<16;sc++){
  if (s[sc].id!=0){
   if (sc>0) buf[a++]=", ";
   if (sc == snum && snum>0) buf[a++]=DE_UNDNOMEN;
   buf[a++]=getArticle(s[sc].id,s[sc].plural?1:0,s[sc].num,0,s[sc].typ);
   for (int i=0;i<16;i++){
    if (sadj[sc][i]!=0)
     buf[a++]=getAdjective(sadj[sc][i],s[sc].id,s[sc].plural,s[sc].typ,0);
   }
   buf[a++]=getNoun(s[sc].id,s[sc].plural,0);
  }
 }
 if (idobj.id!=0){
  buf[a++]=getArticle(idobj.id,idobj.plural?1:0,idobj.num,2,idobj.typ);
  buf[a++]=getNoun(idobj.id,idobj.plural,2);
 }
 for (int oc=0;oc<16;oc++){
  if (o[oc].id!=0){
   buf[a++]=getArticle(o[oc].id,o[oc].plural?1:0,o[oc].num,getCaseOfObject(0,st),o[oc].typ);
  }
  for (int i=0;i<16;i++){
   if (oadj[oc][i]!=0){
    buf[a++]=getAdjective(oadj[oc][i],o[oc].id,o[oc].plural,o[oc].typ,getCaseOfObject(0,st));
   }
  }
  if (o[oc].id!=0){
   buf[a++]=getNoun(o[oc].id,o[oc].plural,getCaseOfObject(0,st));
  }
 }
 if(prepos_prepos[0]!=0){
  buf[a++]=getPreposObject(prepos_prepos[0],prepos_object[0].id,prepos_object[0].num,prepos_object[0].plural,prepos_object[0].typ);
 }
 if(prepos_prepos[1]!=0){
  buf[a++]=getPreposObject(prepos_prepos[1],prepos_object[1].id,prepos_object[1].num,prepos_object[1].plural,prepos_object[1].typ);
 }
 if (neg){
  buf[a++]=de_nicht;
 }
 if (getPreVerb2(v1)==1)
  buf[a++]=de_zu;
 if (v2!=0)
  buf[a++]=getOtherVerb(v1,v2);
 //Get hasEndVerb
 getVerb(v1,-1,splural?8:s[0].id,st);
 if (hasEndVerb)
  buf[a++]=endVerb;
 //Verb goes at the end

 buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st);
 int sl=0;
 for (int i=0;i<256;i++){
  if(buf[i]!=NULL)
   sl+=strlen(buf[i]);
 }
 char* buffer = (char*)calloc(sl+4,sizeof(char));
 for (int i=0;i<256;i++){
  if(buf[i]!=NULL)
   strcat(buffer,buf[i]);
 }
 return buffer;
}
char* de::createSentence(){

 if(verb1!=0){
  parseVerb(0,verb1);
  verb1=0;
 }
 if (verb2!=0){
  parseVerb(1,verb2);
  verb2=0;
 }
 char debug='a';
 int a=0;
 hasEndVerb=false;
 verbs[0]=v1;
 verbs[1]=v2;
 verbs[2]=v3;
 bool verb=false;
 bool splural=(snum>0) | s[0].plural;
 if(v1!=0) verb=true;
 if(data&0x1){
  if(verb) buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st);
  verb = false;
 }
 if (prepos_prepos[2]!=0){
  buf[a++]=getPreposObject(prepos_prepos[2],prepos_object[2].id,prepos_object[2].num,prepos_object[2].plural,prepos_object[2].typ);
  if(verb) buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st);
  verb = false;
 }
 for(int sc=0;sc<16;sc++){
  if (s[sc].id!=0){
   if (sc>0) buf[a++]=", ";
   if (sc == snum && snum>0) buf[a++]=DE_UNDNOMEN;
   buf[a++]=getArticle(s[sc].id,s[sc].plural?1:0,s[sc].num,0,s[sc].typ);
   for (int i=0;i<16;i++){
    if (sadj[sc][i]!=0)
     buf[a++]=getAdjective(sadj[sc][i],s[sc].id,s[sc].plural,s[sc].typ,0);
   }
   buf[a++]=getNoun(s[sc].id,s[sc].plural,0);
  }
 }
 if(verb)buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st);
 if (idobj.id!=0){
  buf[a++]=getArticle(idobj.id,idobj.plural?1:0,idobj.num,2,idobj.typ);
  buf[a++]=getNoun(idobj.id,idobj.plural,2);
 }
 for (int oc=0;oc<16;oc++){
  if (o[oc].id!=0){
   if (oc>0) buf[a++]=", ";
   if (oc == onum && onum>0) buf[a++]=DE_UNDNOMEN;
   buf[a++]=getArticle(o[oc].id,o[oc].plural?1:0,o[oc].num,getCaseOfObject(0,st),o[oc].typ);
  }
  for (int i=0;i<16;i++){
   if (oadj[oc][i]!=0){
    buf[a++]=getAdjective(oadj[oc][i],o[oc].id,o[oc].plural,o[oc].typ,getCaseOfObject(0,st));
   }
  }
  if (o[oc].id!=0){
   buf[a++]=getNoun(o[oc].id,o[oc].plural,getCaseOfObject(0,st));
  }
 }
 if(prepos_prepos[0]!=0){
  buf[a++]=getPreposObject(prepos_prepos[0],prepos_object[0].id,prepos_object[0].num,prepos_object[0].plural,prepos_object[0].typ);
 } 
 if(prepos_prepos[1]!=0){
  buf[a++]=getPreposObject(prepos_prepos[1],prepos_object[1].id,prepos_object[1].num,prepos_object[1].plural,prepos_object[1].typ);
 }
 if (neg){
  buf[a++]=de_nicht;
 }
 if (getPreVerb2(v1)==1)
  buf[a++]=de_zu;
 if (v2!=0)
  buf[a++]=getOtherVerb(v1,v2);
 if (hasEndVerb)
  buf[a++]=endVerb;
 if(subClause!=NULL && conjunction != 0)
 {
  buf[a++]=getSubClause();
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
