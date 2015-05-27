#include "de.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * endVerb;
char es[2]="";
char* de::getVerbPresent(int v, int f, int s, int st){
 if (f<0){
  char t=getNounType(s);
  f=getVerbFormFromSubjectType(s,t);
 }
 FILE* rFile=fopen(DICTIONARY DE_FOLDER "verb_present","r");
 gotoline(rFile,v);
 char* buffer = (char*)malloc(BUFFER_SIZE);
 fgets(buffer,BUFFER_SIZE-1,rFile);
 fclose(rFile);
 char vt=buffer[0];
 char of=f;
 if (vt!='0') f=0;
 int u=0;
 int i=0;
 if (vt=='2' && f!=-2) f++;
 while (u<=f){
  char c=buffer[i];
  if (c=='_') u++;
  else if (c=='\n'){
   printf("Warning:\nThe form %d doesn't exist for verb %d!\nUsing form 0\n",f,v);
   return getVerbPresent(v,0,s,0);
  }
  i++;
 }
 //i should be at the start of form we want
 //copy form to start of buffer
 u=0;
 while (buffer[i]!='_' && buffer[i]!='\n' && buffer[i]!=0){
  buffer[u++]=buffer[i++];
 }
 int es=u+1;
 if(vt=='2'){
  while (buffer[i]!='_' && buffer[i]!='\n' && buffer[i]!=0){
   i++;
  }
  buffer[i]=0;
  endVerb=&buffer[es];
  hasEndVerb=true;
 } 
 if(vt!='0'){
  u--;
  if (buffer[u]=='n') buffer[u--]=' ';
  if (buffer[u]=='e') buffer[u]=' ';
  if (of==1) buffer[u++]='e';
  else if (of==2){ buffer[u++]='s'; buffer[u++]='t';}
  else if (of==3 || of==4 || of==5) buffer[u++]='t';
  else if (of==6 || of==8 || of==9 || of==0){ buffer[u++]='e'; buffer[u++]='n';}
  else if (of==7) buffer[u++]='t';
 }
 buffer[u++]=' ';
 buffer[u++]=0;
 char* ret=(char*)calloc(BUFFER_SIZE,sizeof(char));
 strcat(ret,buffer);
 return ret; 
}
char* de::getVerbPerfekt(int v,int f,int s,int st){
 #ifdef DE_AUTOCHANGESIMPLE
  if (v < 2)
   return getVerbSimple(v,f,s,st);
 #endif
 FILE* rFile=fopen(DICTIONARY DE_FOLDER "verb_pastperfekt","r");
 gotoline(rFile,v);
 char* buffer = (char*)malloc(BUFFER_SIZE);
 fgets(buffer,BUFFER_SIZE-1,rFile);
 fclose(rFile);
 char vt=buffer[0];
 //what we do here, is , we save the past participle for later, and return the helper verb, when we need to get the past participle the create sentence() just reads the endVerb variable
 int i=0;
 int u=0;
 while (u<1){
  if (buffer[i]=='_') u++;
  i++;
 }
 endVerb=&buffer[i];
 hasEndVerb=true;
 while (u<2){
  if (buffer[i]=='\n'){
   buffer[i]=' ';
   buffer[i+1]=0;
   u++;
  }
  i++;
 }
 //haben
 if (vt=='0'){
  return getVerbPresent(2,f,s,0);
 }else if (vt=='1'){ 
 //sein
  return getVerbPresent(1,f,s,0);
 }
}
char* de::getVerbSimple(int v,int f,int s,int st){
 if (f<0){
  char t=getNounType(s);
  f=getVerbFormFromSubjectType(s,t);
 }
 FILE* rFile=fopen(DICTIONARY DE_FOLDER "verb_simple","r");
 gotoline(rFile,v);
 char* buffer = (char*)malloc(BUFFER_SIZE);
 fgets(buffer,BUFFER_SIZE-1,rFile);
 fclose(rFile);
 char vt=buffer[0];
 if (vt == '1') return getVerbPerfekt(v,f,s,st);
 int i=0;
 int u=0;
 while (u<1){
  if (buffer[i]=='_') u++;
  i++;
 }
 int a = i;
 while (u<2){
  if (buffer[i]=='\n'){
   //Need to conjugate here
   if (f==2){ buffer[i++]='s'; buffer[i++]='t';}
   else if (f==6 || f==8 || f==9){ if (buffer[i-1]!='e') buffer[i++]='e'; buffer[i++]='n';}
   else if (f==7) buffer[i++]='t';
   buffer[i]=' ';
   buffer[i+1]=0;
   u++;
  }
  i++;
 }
 return &buffer[a];
}
char* de::getOtherVerb(int v1,int v2){
 return getVerbPresent(v2,0,0,0);
}
char* de::getVerbFuture(int v,int f,int s,int st){
 char* verb = getVerbPresent(v,0,0,0);
 char* hilfsverb = getVerbPresent(14,-1,s,0);
 endVerb = verb;
 hasEndVerb = true;
 return hilfsverb;
}
char* de::getVerbFuturePerfekt(int v,int f,int s,int st){
 char* verb = getVerbPerfekt(v,0,0,2);
 char* hilfsverb = getVerbPresent(14,-1,s,0);
 if (!hasEndVerb)
  return (char*)"FAIL DE:GVFP()";
 char* ev = (char*)malloc(strlen(endVerb) + strlen(verb) + 1);
 ev[0] = 0;
 strcat(ev,endVerb);
 strcat(ev,verb);
 endVerb = ev;
 return hilfsverb;
}
char* de::getVerbPassivePresent(int v,int f,int s,int st)
{
 char* hilfsverb = getVerbPresent(14,f,s,0);
 //Set the endVerb
 getVerbPerfekt(v,2,0,0);
 return hilfsverb;
}
char* de::getVerbPassivePast(int v,int f,int s,int st)
{
 char* hilfsverb = getVerbSimple(14,f,s,3);
 getVerbPerfekt(v,2,0,0);
 return hilfsverb;
}
char* de::getVerbPassiveFuture(int v,int f,int s,int st)
{
 char* hilfsverb = getVerbPresent(14,f,s,0);
 char* hilfs2verb = getVerbPresent(14,-1,0,0);
 getVerbPerfekt(v,2,0,0);
 char* ev = (char*)malloc(strlen(endVerb) + strlen(hilfs2verb) + 1);
 ev[0]=0;
 strcat(ev,endVerb);
 strcat(ev,hilfs2verb);
 endVerb = ev;
 return hilfsverb;
}
char* de::getVerb(int v, int f, int s, int st)
{
 if (st<2){
  return getVerbPresent(v,f,s,st);
 }else if (st<10 && !(st&0x01)){
  return getVerbPerfekt(v,f,s,st);
 }else if (st<10 && st&0x01){
  return getVerbSimple(v,f,s,st);
 }else if (st<14){
  return getVerbFuture(v,f,s,st);
 }else if (st<16){
  return getVerbFuturePerfekt(v,f,s,st);
 }else if (st<18){
  return getVerbPassivePresent(v,f,s,st);
 }else if (st<26){
  return getVerbPassivePast(v,f,s,st);
 }else if (st<32){
  return getVerbPassiveFuture(v,f,s,st);
 }
}
