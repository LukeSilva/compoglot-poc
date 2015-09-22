#include "de.h"
#include "../Language.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char de::getNounType(int n){
 FILE* rFile = fopen(DICTIONARY DE_FOLDER "nouns","r");
 gotoline(rFile,n);
 char ret = fgetc(rFile);
 fclose(rFile);
 return ret;
}
char* de::getNoun(int n,bool pl,int cas){
 FILE* rFile = fopen(DICTIONARY DE_FOLDER "nouns","r");
 gotoline(rFile,n);
 char* buf=(char*)calloc(BUFFER_SIZE,sizeof(char));
 int f=pl?1:0;
 if (getNounType(n)=='P') f=cas;
 fgets(buf,BUFFER_SIZE-1,rFile);
 int i=0;
 int u=0;
 while(u<=f)
 {
  if (buf[i]=='_'){
   u++;
  }else if (buf[i]=='\n') break;
  i++;
 }
  u=0;
 while (buf[i]!='_' && buf[i]!=0 && buf[i]!='\n'){
  buf[u++]=buf[i++];}
 buf[u++]=' ';
 buf[u]=0;
 fclose(rFile);
 return buf;
}
