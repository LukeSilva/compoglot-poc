#include "en.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char blank=0;
char negativestmt[5]="not ";
char donot[8]=EN_EN_DONOT;
char* en_en::getVerbPreAdd(int v){
 FILE* rFile=fopen(DICTIONARY EN_EN_FOLDER "verb_present","r");
 gotoline(rFile,v);
 char* buffer=(char*)malloc(BUFFER_SIZE);
 fgets(buffer,BUFFER_SIZE-1,rFile);
 fclose(rFile);
 char t=buffer[0];
 if (t=='1'){
  //Look up second word form
  int u=0,i=0;
  while (u<2){
   if (buffer[i]=='_')
    u++;
   else if (buffer[i]==0)
    break;
   else if (buffer[i]=='\n')
    break;
   i++;
  }
  u=0;
  while (buffer[i]!='_' && buffer[i]!=0 && buffer[i]!='\n')
   buffer[u++]=buffer[i++];
  buffer[u++]=0;
 }else if (t=='0'){
  char* b=getVerb(v,10,0,1,&blank);
  int i=0;
  while (b[i]!=0) i++;
  //[(space)] [\0]
  //We are removing the space here, because it is added in getVerb because the function thinks we will just add it straight to the sentence.
  b[i-1]=0;
  return b;
 }else{
  int i=0;
  while(buffer[i]!='_' && buffer[i]!=0 && buffer[i]!='\n') i++;
  i++;
  int u=0;
  while (buffer[i]!='_' && buffer[i]!=0 && buffer[i]!='\n')
   buffer[u++]=buffer[i++];

  //Now follow all the english rules
  //http://www.oxforddictionaries.com/words/verb-tenses-adding-ed-and-ing
  //http://www.grammar.cl/Notes/Spelling_ING.htm
  if (buffer[u-1]=='e' && buffer[u-2]=='i'){
   u-=2;
   buffer[u++]='y';
  }
  else if (buffer[u-1]=='e' && (buffer[u-2]!='e' && buffer[u-2]!='y' && buffer[u-2]!='o'))
   u-=1;
  else if (buffer[u-1]=='c'){
   buffer[u++]='k';
  }
  else if (!isVowel(buffer[u-3])&&isVowel(buffer[u-2])&&!isVowel(buffer[u-1])&&buffer[u-1]!='x'&&buffer[u-1]!='y'&&buffer[u-1]!='z'&&buffer[u-1]!='w'){
   buffer[u]=buffer[u-1];
   u++;
  }
  buffer[u++]=0;
 }
 return buffer;
}
char* en_en::getVerbPresent(int v,int f,int s,int st,char* midadverb){
  if (f==-1){
   int t=getNounType(s);
   f=getVerbFormFromSubjectType(t,s);
  }
  if (st==1){
   FILE* rFile = fopen(DICTIONARY EN_EN_FOLDER "verb_present","r");
   gotoline(rFile,v);
   char* buffer = (char*)malloc(BUFFER_SIZE);
   fgets(buffer,BUFFER_SIZE-1,rFile);
   fclose(rFile);
   char vt=buffer[0];
   char of=f;
   if (vt!='0') f=0;
   int u=0;
   int i=0;
   while (u<=f){
    char c=buffer[i];
    if (c=='_') u++;
    else if (c=='\n'){
     printf("Warning:\nThe form %d doesn't exist for verb %d!\nUsing form 0\n",f,v);
     return getVerb(v,0,s,1,midadverb);
    }
    i++;
   }
   //i should be at the start of form we want
   //copy form to start of buffer
   u=0;
   while (buffer[i]!='_' && buffer[i]!='\n' && buffer[i]!=0){
    buffer[u++]=buffer[i++];
   }
   //Now if SIMPLE tense on a regular verb, add conjugation
   if (vt!='0' && vt!='3' ){
    if (of>2 && of<6){
     if (buffer[u-1]=='o' || (buffer[u-1]=='s' && buffer[u-2]=='s') || (buffer[u-1]=='h' && buffer[u-2]=='s') || (buffer[u-1]=='h' && buffer[u-2]=='c') || (buffer[u-1]=='z' && buffer[u-2]=='z') || buffer[u-1]=='x')
      buffer[u++]='e';
     buffer[u++]='s';
    }
   }
   buffer[u++]=' ';
   buffer[u++]=0;
   if (neg && (vt=='3' || vt=='0')){
    strcat(buffer,negativestmt);
   }
   char* ret=(char*)calloc(BUFFER_SIZE,sizeof(char));
   strcat(ret,midadverb);
   if (neg && vt!='3' && vt!='0'){
    if (of>2 && of<6)
     strcat(ret,EN_EN_DOESNOT);
    else
     strcat(ret,donot);
   }
   strcat(ret,buffer);
   return ret;
  }
  else if (st==0){
   char t=getVerbType(v,st);
   if (t=='4'||t=='3'){
   // printf("Can not create progressive tense with type %c verbs!\nUsing simple tense instead.\n",t);
    return getVerb(v,f,s,1,midadverb);
   }
   int bl,il;
   bl=getVerbLength(1,f,s,1,&blank);
   char* preadd=getVerbPreAdd(v);
   il=strlen(preadd);
   char* gerund=NULL;
   char* buffer = NULL;
   if (question==0)
   {
    buffer = (char*)calloc(bl+il+5,sizeof(char));
    gerund = buffer;
   }
   else if (question>0)
   {
    buffer = (char*) calloc(bl+1,sizeof(char));
    QuestionVerb1 = (char*) calloc(il+5,sizeof(char));
    gerund = QuestionVerb1;
   }
   strcat(buffer,getVerb(1,f,s,1,&blank));
   strcat(buffer,midadverb);
   strcat(gerund,preadd);
   strcat(gerund,"ing ");
   return buffer;
  }
}
char* en_en::getVerbPast(int v,int f, int s,bool dr,char* midadverb)
{
 FILE* rFile = fopen(DICTIONARY EN_EN_FOLDER "verb_past","r");
 gotoline(rFile,v);
 char* buffer=(char*)malloc(BUFFER_SIZE); 
 fgets(buffer,BUFFER_SIZE-1,rFile);
 fclose(rFile);
 char vt=buffer[0];
 //just return preadd + (vt=='2' ? 'd' : 'ed' )
 if (vt=='2' || vt=='3')
 {
  int el=vt-'1';
  char* preadd=getVerbPreAdd(v);
  int il=strlen(preadd);
  char* buffer2=(char*)calloc(il+el,sizeof(char));
  strcat(buffer2,midadverb);
  strcat(buffer2,preadd);
  if (vt=='3') strcat(buffer2,"e");
  strcat(buffer2,"d ");
 // free(buffer);
  return buffer2;
 }
 else if (vt=='1')
 {
  int i=1;
  int f=dr?2:1;
  int u=0;
  while (u<f)
  {
   if (buffer[i]=='_')
    u++;
   if (buffer[i]=='\n')
    break;
   i++;
  }
  char* buffer2=(char*)calloc(BUFFER_SIZE,sizeof(char));
  strcat(buffer2,midadverb);
  u=strlen(buffer2);
  while(1){
   buffer2[u]=buffer[i];
   i++;
   u++;
   if(buffer[i]=='\n' || buffer[i]=='_')
    break;
  }
  buffer2[u++]=' ';
  buffer2[u++]=0;
  return buffer2;
 }
 else if (vt=='0' || vt=='4'){
  if (f==-1){
   int t=getNounType(s);
  f=getVerbFormFromSubjectType(t,s);
  }
  char of=f;
  if (dr) f = 0;
  int u=0;
  int i=0;
  while (u<=f){
   char c=buffer[i];
   if (c=='_') u++;
   else if (c=='\n'){
    printf("Warning:\nThe form %d doesn't exist for verb %d!\nUsing form 0\n",f,v);
    return getVerb(v,0,s,1,&blank);
   }
   i++;
  }
  //i should be at the start of form we want
  //copy form to start of buffer
  char* buffer2=(char*)calloc(BUFFER_SIZE,sizeof(char));
  strcat(buffer2,midadverb);
  u=strlen(buffer2);
  while (buffer[i]!='_' && buffer[i]!='\n' && buffer[i]!=0){
   buffer2[u++]=buffer[i++];
  }
  buffer2[u++]=' ';
  buffer2[u++]=0;
  return buffer2;
 }
 else{
  printf("ERROR:\n");
 }
 return (char*)"failure in en_en::getVerbPast() ";
}

char* en_en::getVerbPastProgressive(int v,int f,int s,int st,char* midadverb){
 char t = getVerbType(v,st);
 if (st<6 && t!='4')
 {
  int bl,il;
  bl=getVerbLength(1,f,s,st-2,&blank);
  char* preadd=getVerbPreAdd(v);
  il=strlen(preadd);   
  char* gerund = NULL;
  char* buffer = NULL;
  if (question==0)
  {
   buffer = (char*)calloc(bl+il+5,sizeof(char));
   gerund = buffer;
  }
  else if (question==1)
  {
   buffer = (char*) calloc(bl+1,sizeof(char));
   QuestionVerb1 = (char*) calloc(il+5,sizeof(char));
   gerund = QuestionVerb1;
  }
  strcat(buffer,getVerb(1,f,s,st-2,&blank));
  strcat(gerund,midadverb);
  strcat(gerund,preadd);
  strcat(gerund,"ing ");
  return buffer;
 }else if(st<10 && t!='4'){
   int bl,il;
  bl=getVerbLength(2,f,s,1,&blank);
  bl+=getVerbLength(1,0,s,3,midadverb);
  char* preadd=getVerbPreAdd(v);
  il=strlen(preadd);
  char* gerund = NULL;
  char* buffer = NULL;
  if (question==0)
  {
   buffer = (char*)calloc(bl+il+5,sizeof(char));
   gerund = buffer;
  }
  else if (question==1)
  {
   buffer = (char*) calloc(bl+1,sizeof(char));
   QuestionVerb1 = (char*) calloc(il+5,sizeof(char));
   gerund = QuestionVerb1;
  }
  strcat(buffer,getVerb(2,f,s,1,&blank));
  strcat(gerund,getVerbPast(1,0,s,3,midadverb));
  strcat(gerund,preadd);
  strcat(gerund,"ing ");
  return buffer;
 }else if (t=='4'){
   return getVerbPast(v,f,s,4,(char*)"");
 }
 else{
  printf("OOPS");
 }
}
char* en_en::getVerbPast(int v,int f,int s,int st,char* midadverb){
 if (st<4 || getVerbType(v,st)=='4')
  return getVerbPast(v,f,s,false,midadverb);
 else if (question==0)
  return strcat(getVerbPresent(2,f,s,1,&blank),getVerbPast(v,f,s,true,midadverb));
 else if (question==1){
  QuestionVerb1 = getVerbPast(v,f,s,true,midadverb);
  return getVerbPresent(2,f,s,1,&blank);
 }
}
char* en_en::getOtherVerb(int v1,int v2,int* adv){
 char* adverbs = "";
 char t = '1';
 if (v1!=0)
 {
  FILE* rFile = fopen(DICTIONARY EN_EN_FOLDER "verb_present","r");
  gotoline(rFile,v1);
  fgetc(rFile);
  t = fgetc(rFile);
  fclose(rFile);
 }else
 {
  adverbs = getMiddleAdverbs(adv);
 }

 char* buf = (char*)calloc(BUFFER_SIZE,sizeof(char));
 if (t=='2'){ 
  strcat(buf,getVerbPreAdd(v2));
  strcat(buf,"ing ");
 }else if (t=='3'){
  strcat(buf,getVerbPresent(v2,-1,0,1,adverbs));
 }else if (t=='1'){
  strcat(buf,"to ");
  strcat(buf,getVerbPresent(v2,-1,0,1,adverbs));
 }
 return buf;
}
char* en_en::getVerbFutureSimple(int v, int f, int s, int st, char* midadverb){
  char* verb;
  verb = getVerbPresent(v,f,1,1,midadverb);
  char* buf = (char*)calloc(sizeof(verb) + sizeof(EN_EN_FUTURE) + 1,sizeof(char));
  strcat(buf,EN_EN_FUTURE);
  strcat(buf,verb);
  return buf;
}
char* en_en::getVerbFutureProgressive(int v, int f, int s, int st, char* midadverb){
  char* verb;
  verb = getVerbPresent(v,f,0,0,midadverb);
  char* buf = (char*)calloc(sizeof(verb) + sizeof(EN_EN_FUTURE) + 1,sizeof(char));
  strcat(buf,EN_EN_FUTURE);
  strcat(buf,verb);
  return buf;
}
char* en_en::getVerbFuturePastSimple(int v, int f, int s, int st, char* midadverb){
  char* verb;
  verb = getVerb(v,f,1,6,midadverb);
  char* buf = (char*)calloc(sizeof(verb) + sizeof(EN_EN_FUTURE) + 1,sizeof(char));
  strcat(buf,EN_EN_FUTURE);
  strcat(buf,verb);
  return buf;
}
char* en_en::getVerbFuturePastProgressive(int v, int f, int s, int st, char* midadverb){
  char* verb;
  verb = getVerb(v,f,1,8,midadverb);
  char* buf = (char*)calloc(sizeof(verb) + sizeof(EN_EN_FUTURE) + 1,sizeof(char));
  strcat(buf,EN_EN_FUTURE);
  strcat(buf,verb);
  return buf;
}
char* en_en::getVerbPassivePresent(int v,int f,int s,int st, char* midadverb){
  if (st > 25) f = 0;
  char* fv = getVerb(1,f,s,st - 16,&blank);
  char* sv = getVerbPast(v,f,s,true,midadverb);
  char* buf = (char*) calloc(sizeof(fv) + sizeof(sv) + 1,sizeof(char));
  strcat(buf,fv);
  strcat(buf,sv);
  return buf;
}
char* en_en::getVerb(int v, int f,int s, int st,char* midadverb){
  if (st < 2)
   return getVerbPresent(v,f,s,st,midadverb);
  else if(st<4)
   return getVerbPast(v,f,s,st,midadverb);
  else if(st<6)
   return getVerbPastProgressive(v,f,s,st,midadverb);
  else if (st<8)
   return getVerbPast(v,f,s,st,midadverb);
  else if (st<10)
   return getVerbPastProgressive(v,f,s,st,midadverb);
  else if (st==10 || st == 12)
   return getVerbFutureSimple(v,f,s,st,midadverb);
  else if (st==11 || st == 13)
   return getVerbFutureProgressive(v,f,s,st,midadverb);
  else if (st==14)
   return getVerbFuturePastSimple(v,f,s,st,midadverb);
  else if (st==15)
   return getVerbFuturePastProgressive(v,f,s,st,midadverb);
  else if (st<31)
   return getVerbPassivePresent(v,f,s,st,midadverb);
  char* buffer = (char*)malloc(10);
  buffer[0]=0;
  return buffer;
}
int en_en::getVerbLength(int v,int f,int s,int st,char* midadverb){
  char* buffer=getVerb(v,f,s,st,midadverb);
  int l=strlen(buffer);
  return l;
}
