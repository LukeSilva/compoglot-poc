#include "en.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* en_en::getConjunction(int conjunction){
 FILE* rFile=fopen(DICTIONARY EN_EN_FOLDER "conjunctions","r"); 
 gotoline(rFile,conjunction);
 char* buf = (char*)calloc(BUFFER_SIZE,sizeof(char));
 fgets(buf,BUFFER_SIZE-1,rFile);
 fclose(rFile);
 for (int i=0;i<BUFFER_SIZE;i++)
 {
  if (buf[i]=='\n') buf[i]=0;
 }
 return buf;
}


char* en_en::getSubClause(int conjunction,Language* subClause)
{
  char* conjunc = getConjunction(conjunction);
  subClause->clause=true;
  char* clause = (char*)subClause->createSentence().c_str();
  char* buffer = (char*)calloc(strlen(conjunc)+strlen(clause)+3,sizeof(char));
  strcat(buffer,", ");
  strcat(buffer,conjunc);
  strcat(buffer," ");
  strcat(buffer,clause);
  return buffer;
}
