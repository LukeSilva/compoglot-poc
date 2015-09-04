#include "en.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**  
     returns number of _ you must reach +1 to get to a specific form of noun
     returns -2 to add a single 's' character to make the noun a plural
     returns -1 if the form is not available in this noun (should never be returned unless you do something wrong)
     returns -4 if the form should be found in another noun 
**/
int en_en::hasform(int s,int form){
 FILE* rFile = fopen (DICTIONARY EN_EN_FOLDER "nouns","r");
 if(rFile==NULL)
  printf("Failed to open file:%s\n",DICTIONARY EN_EN_FOLDER "nouns");
 gotoline(rFile,s);
 char t=fgetc(rFile);
 fclose(rFile);
 if (t=='d' && form<4)
  return form;
 else if ((t=='m' || t=='f' || t=='n' || t=='b') && form<3) return 0;
 else if ((t=='m' || t=='f' || t=='n' || t=='b') && form== 4) return -2;
 else if (t=='o' && form==4) return 1;
 else if (t=='o' && form<3) return 0;
 else if (t=='p' && form==4) return 1;
 else if (t=='p' && form<4) return 0;
 else if (form==3) return -4;
 return -1;
}

//used when en_en_hasform returns -4 to get the "another noun"
int en_en::getNewNoun(int s)
{
  FILE* rFile = fopen(DICTIONARY EN_EN_FOLDER "nouns","r");
  gotoline(rFile,s);
  char t=fgetc(rFile);
  if (t=='n' || t=='o' || t=='b')
   return 5;
  if (t=='m')
   return 3;
  if (t=='f')
   return 4;
  if (t=='p')
   return 10;
  return 1;
}
char* en_en::getNoun(int s,int form){
 int nform = hasform(s,form);
 //printf("hasform returned %d\n",nform);
 if (nform>=0)
  form=nform;
 else if (nform==-4)
  return getNoun(getNewNoun(s),form);
 else if (nform==-2)
  form=0;
 else if (nform==-1)
 {
  printf("Oh noes! Can't get form for %d,form=%d,nform=-1;\n",s,form);
  printf("Assmuming you meant form=0\n");
  form=0;
 }
 FILE* rFile = fopen(DICTIONARY EN_EN_FOLDER "nouns","r");
 gotoline(rFile,s);
 char* buffer = (char*)malloc(BUFFER_SIZE);
 fgets(buffer,BUFFER_SIZE-1,rFile);
 form+=1;
 int u=0,i=0;
 while (form>u){
  if (buffer[i]==0) break;
  if (buffer[i++]=='_')
  {
   u++;
  }
 }
 u=0;
 while (buffer[i]!='_' && buffer[i]!=0 && buffer[i]!='\n'){
  buffer[u++]=buffer[i++];}
 if (nform==-2)
  buffer[u++]='s';
 buffer[u++]=' ';
 buffer[u]=0;
// puts(buffer);
 fclose(rFile);
 return buffer;
}

int en_en::getNounLength(int s,int form){
 return strlen(getNoun(s,form));
}

char en_en::getNounType(int s){
 FILE* rFile = fopen(DICTIONARY EN_EN_FOLDER "nouns","r");
 gotoline(rFile,s);
 char t=fgetc(rFile);
 fclose(rFile);
 return t;
}
