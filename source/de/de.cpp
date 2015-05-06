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
char* de::getNounString(noun* n)
{
	if (n->data < 0) n->data = 0;
 char* buffer = (char*) malloc (BUFFER_SIZE*10);
 buffer[0]=0;
 int cas = n->data;
 bool doArticle = true;
 if (n->prepos!=0)
 {
  strcat(buffer,getPreposObject(n->prepos,n,&cas,&doArticle));
 }
 strcat(buffer,getArticle(n->id,n->plural?1:0,n->num,n->data,n->typ));
 for (int i=0;i<16;i++){
  if (n->adj[i]!=0)
   strcat(buffer,getAdjective(n->adj[i],n->id,n->plural,n->typ,n->data));
 }
 strcat(buffer,getNoun(n->id,n->plural,n->data));
 if (n->usegenitive)
 {
  n->genitivenoun->data = 3;
  //Force definate article if not yet defined.
  if (n->genitivenoun->typ == 0)
    n->genitivenoun->typ = -1;
  strcat(buffer,getNounString(n->genitivenoun));
 }
 if (n->useRClause)
 {
  strcat(buffer,", ");
  char* rClauseString =n->rClause->createSubClause();
  int cas2 = 0;
  if (n->rClauseObj != 0)
  {
    cas2 = n->rClause->obj[n->rClauseObj-1][0].data;
  }
  else cas2 = n->rClause->s[0].data;
  strcat(buffer,getArticle(n->id,n->plural?1:0,n->num,cas2,-1));
  strcat(buffer,rClauseString);
 }
 return buffer;
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
 if(verb1>0){
  parseVerb(0,verb1);
  verb1=0;
 }
 if (verb2>0){
  parseVerb(1,verb2);
  verb2=0;
 }
 int a=0;
 hasEndVerb=false;
 verbs[0]=v1;
 verbs[1]=v2;
 verbs[2]=v3;
 bool splural=(snum>0) | s[0].plural;
/* if (prepos_prepos[2]!=0){
  buf[a++]=getPreposObject(prepos_prepos[2],prepos_object[2].id,prepos_object[2].num,prepos_object[2].plural,prepos_object[2].typ);
 }*/
 for(int sc=0;sc<16;sc++){
  if (s[sc].id>0){
   if (sc>0) buf[a++]=", ";
   if (sc == snum && snum>0 && sctype==0) buf[a++]=DE_UNDNOMEN;
   else if (sc == snum && snum>0) buf[a++]=DE_ODERNOMEN;
   buf[a++]=getNounString(&s[sc]);
  }
 }
 for (int objid=0;objid<8;objid++){
  for (int oc=0;oc<16;oc++){
   if (obj[objid][oc].id>0){
    if (oc>0) buf[a++]=", ";
    if (oc == objnum[objid] && objnum[objid]>0 && octype[objid]==0) buf[a++]=DE_UNDNOMEN;
    else if (oc == objnum[objid] && objnum[objid]>0) buf[a++] = DE_ODERNOMEN;
    buf[a++]=getNounString(&obj[objid][oc]);
   }
  }
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
 
 if(subClause!=NULL && conjunction > 0)
 {
  buf[a++]=getSubClause();
 }
 int sl=0;
 for (int i=0;i<NUM_BUF;i++){
  if(buf[i]!=NULL)
   sl+=strlen(buf[i]);
 }
 char* buffer = (char*)calloc(sl+4,sizeof(char));
 for (int i=0;i<NUM_BUF;i++){
  if(buf[i]!=NULL)
   strcat(buffer,buf[i]);
 }
 return buffer;
}
char* de::createSentence(){
 char endchar = '.';
 if (question == 1){
  data|=0x01;
  endchar = '?';
 }
 if (punctuation == false)
  endchar = NULL;
 if(verb1>0){
  parseVerb(0,verb1);
  verb1=0;
 }
 if (verb2>0){
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
 /*if (prepos_prepos[2]>0){
  buf[a++]=getPreposObject(prepos_prepos[2],prepos_object[2].id,prepos_object[2].num,prepos_object[2].plural,prepos_object[2].typ);
  if(verb) buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st);
  verb = false;
 }*/
 for(int sc=0;sc<16;sc++){
  if (s[sc].id>0){
   if (sc>0) buf[a++]=", ";
   if (sc == snum && snum>0 && sctype==0) buf[a++]=DE_UNDNOMEN;
   else if (sc == snum && snum>0) buf[a++]=DE_ODERNOMEN;
   buf[a++]=getNounString(&s[sc]);
  }
 }
 if(verb)buf[a++]=getVerb(v1,-1,splural?8:s[0].id,st);
 for (int objid=0;objid<8;objid++){
  for (int oc=0;oc<16;oc++){
   if (obj[objid][oc].id>0){
    if (oc>0) buf[a++]=", ";
    if (oc == objnum[objid] && objnum[objid]>0 && octype[objid]==0) buf[a++]=DE_UNDNOMEN;
    else if (oc == objnum[objid] && objnum[objid]>0) buf[a++] = DE_ODERNOMEN;    
    buf[a++]=getNounString(&obj[objid][oc]);
   }
  }
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
 if(subClause!=NULL && conjunction > 0)
 {
  buf[a++]=getSubClause();
 }
 int sl=0;
 for (int i=0;i<NUM_BUF;i++){
  if(buf[i]!=NULL)
   sl+=strlen(buf[i]);
 }
 char* buffer = (char*)calloc(sl+4,sizeof(char));
 for (int i=0;i<NUM_BUF;i++){
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
    buffer[j++]=endchar;
    i++;
   }else buffer[j++]=buf2[i++];
  }
 }
 return buffer;
}
