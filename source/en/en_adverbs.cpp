#include "en.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* en_en::getAdverb(int adverbId){
 FILE* rFile=fopen(DICTIONARY EN_EN_FOLDER "adverbs","r");
 gotoline(rFile,adverbId);
 char* buffer=(char*)malloc(BUFFER_SIZE);
 fgets(buffer,BUFFER_SIZE-1,rFile);
 for (int i=2;i<BUFFER_SIZE-1;i++)
 {
  if (buffer[i]=='\n')
  {
   buffer[i]=' ';
   buffer[i+1]=0;
  }
  buffer[i-2]=buffer[i];
 }
 fclose(rFile);
 return buffer;
}
char en_en::getAdverbType(int adverbId){
 if (adverbId==0){
  return ' ';
 } 
 FILE* rFile=fopen(DICTIONARY EN_EN_FOLDER "adverbs","r");
 gotoline(rFile,adverbId);
 char ret=fgetc(rFile);
 fclose(rFile);
 return ret;
}
char* en_en::getMiddleAdverbs(int* adverbs){
 char* buffer = (char*)calloc(BUFFER_SIZE,sizeof(char));
 for (int i=0;i<NUM_ADVERBS;i++){
  if (getAdverbType(adverbs[i])=='m'){
   strcat(buffer,getAdverb(adverbs[i]));
  }
 }
 return buffer;
}
char* en_en::getStartAdverbs(int* adverbs){
 char* buffer = (char*)calloc(BUFFER_SIZE,sizeof(char));
 for (int i=0;i<NUM_ADVERBS;i++){
  if(getAdverbType(adverbs[i])=='s'){ 
   strcat(buffer,getAdverb(adverbs[i]));
  }
 }
 return buffer;
}
char* en_en::getEndAdverbs(int* adverbs){
 char* buffer = (char*)calloc(BUFFER_SIZE,sizeof(char));
 for (int i=0;i<NUM_ADVERBS;i++){
  if(getAdverbType(adverbs[i])=='e'){ 
   strcat(buffer,getAdverb(adverbs[i]));
  }
 }
 return buffer;
}
int en_en::getEndAdverbsLength(int* adverbs){
 char* buffer=getEndAdverbs(adverbs);
 int ret=strlen(buffer);
 return ret;
}
