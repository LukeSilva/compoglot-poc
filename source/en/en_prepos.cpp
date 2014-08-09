#include "en.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* en_en::getPrepos(int prepos){
 FILE* rFile = fopen(DICTIONARY EN_EN_FOLDER "prepos", "r");
 gotoline(rFile,prepos);
 char* buffer = (char*)malloc(BUFFER_SIZE);
 fgets(buffer,BUFFER_SIZE-1,rFile);
 for (int i = 0; i<BUFFER_SIZE;i++)
 {
  if (buffer[i]=='\n'){
   buffer[i]=' ';
   buffer[i+1]=0;
   i=BUFFER_SIZE+1;
  }
 }
 fclose(rFile);
 return buffer;
}
int en_en::getPreposLength(int prepos){ 
 return strlen(getPrepos(prepos));
}
