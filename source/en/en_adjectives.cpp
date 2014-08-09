#include "en.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* en_en::getAdjective(int adj)
{
 FILE* rFile=fopen(DICTIONARY EN_EN_FOLDER "adjectives","r");
 gotoline(rFile,adj);
 char* buffer=(char*)malloc(BUFFER_SIZE);
 fgets(buffer,BUFFER_SIZE-1,rFile);
 for (int i=0;i<BUFFER_SIZE-1;i++)
 {
  if (buffer[i]=='\n')
  {
   buffer[i]=' ';
   buffer[i+1]=0;
  }
 }
 fclose(rFile);
 return buffer;
}
int en_en::getAdjectiveLength(int adj)
{
 char* buffer=getAdjective(adj);
 int ret=strlen(buffer);
 free(buffer);
 return ret;
}
