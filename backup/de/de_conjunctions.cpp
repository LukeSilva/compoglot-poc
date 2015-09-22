#include "de.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* de::getConjunction(int conjunction){
 FILE* rFile = fopen(DICTIONARY DE_FOLDER "conjunctions","r");
 gotoline(rFile,conjunction);
 char* buf = (char*)calloc(BUFFER_SIZE,sizeof(char));
 fgets(buf,BUFFER_SIZE-1,rFile);
 fclose(rFile);
 int i=0;
 while(true){
	 if (buf[i] == '_') break;
  i++;
 }
 i++;
 int u=0;
 while(true){
  buf[u]=buf[i];
  i++;
  u++;
  if(buf[i]=='\n' || buf[i]==0) break;
 }
 buf[u]=0;
 return buf;
}
char de::getConjunctionType(int conjunction){
 FILE * rFile = fopen(DICTIONARY DE_FOLDER "conjunctions","r");
 gotoline(rFile,conjunction);
 char ret =fgetc(rFile);
 fclose(rFile);
 return ret;
}
char* de::getSubClause(){
 char* conjunctionString = getConjunction(conjunction);
 char* clause;
 subClause->clause=true;
 if (getConjunctionType(conjunction)=='2')
  subClause->data|=1;
 if (getConjunctionType(conjunction)=='0')
  clause= (char*) subClause->createSubClause().c_str();
 else clause=(char*)subClause->createSentence().c_str();
 char* buf = (char*)calloc(strlen(clause)+strlen(conjunctionString)+4,sizeof(char));
 strcat(buf,", ");
 strcat(buf,conjunctionString);
 strcat(buf," ");
 strcat(buf,clause);
 return buf;
}
