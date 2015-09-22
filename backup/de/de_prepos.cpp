#include "de.h"
#include "../Language.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* de::getPreposObject(int prepos,noun* n,int* cas,bool* adda){
 int object = n->id;
 FILE* rFile = fopen(DICTIONARY DE_FOLDER "prepos","r");
 gotoline(rFile,prepos);
 char* buf=(char*)calloc(BUFFER_SIZE,sizeof(char));
 fgets(buf,BUFFER_SIZE-1,rFile);
 *cas=buf[0]-'0';
 int a=buf[1]-'0';
 int i=0;
 while(buf[i]!='_') i++;
 i++;
 int u=0;
 while(buf[i]!=' ' && buf[i]!='\n' && buf[i]!=EOF)
 {
  buf[u]=buf[i];
  u++;
  i++;
 }
 bool addarticle=true;
 if (DE_CONTRACTPREPOSITIONS){
  if (a==1 && ( getNounType(object)=='m' || getNounType(object)=='n' ) && n->typ==-1)
  {
   buf[u-1]='m';
   addarticle=false;
  }
  else if ((a==2 || a==3) && ( getNounType(object)=='m' || getNounType(object)=='n' ) && n->typ==-1)
  {
   buf[u++]='m';
   addarticle=false;
  }
  else if (a==3 && getNounType(object)=='f' && n->typ==-1)
  {
   buf[u++]='r';
   addarticle=false;
  }
  else if (a==4 && getNounType(object)=='n' && n->typ==-1)
  {
   buf[u++]='s';
   addarticle=false;
  }
 }
 buf[u++]=' ';
 buf[u]=0;
 *adda = addarticle;
 return buf;
}
