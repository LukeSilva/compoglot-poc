#include "en.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char en_en_articles[4][5]={"the ","a ","an ",""};
char en_en_numerals[12][7]={"","zero ","one ","two ","three ","four ","five ","six ","seven ","eight ","nine ","ten "};

char en_en_article[16][20]={"an ","a ","the ","","my ","your ","his ","her ","its ","our ","your ","their ","your ","a lot of ","this "};

char* en_en::getNumberAsString(int number)
{
 char* buffer = (char*)calloc(BUFFER_SIZE,sizeof(char));
 if (number > 10 || number < -10)
 {
  if (number<0)
   sprintf(buffer,"%d ",number+1);
  else if (number>0)
   sprintf(buffer,"%d ",number-1);
 }else{
  if (number<0)
  {
   strcat(buffer,EN_NEGATIVE);
   strcat(buffer,en_en_numerals[number*-1]);
  }
  else strcat(buffer,en_en_numerals[number]);
 }
 return buffer;
}

int en_en::getArticleLength(int s, int form,int num,int typ)
{
 char* buffer = getArticle(s,form,num,typ);
 int i = strlen(buffer);
 free(buffer);
 return i;
}
char* en_en::getArticle(int s, int form,int num,int typ)
{
 FILE* rFile = fopen(DICTIONARY EN_EN_FOLDER "nouns","r");
 gotoline(rFile,s);
 char t=fgetc(rFile);
 fclose(rFile);
 if (t=='b' && typ==-2) return getArticle(s,form,num,-3);
 char* buffer = (char*)calloc(BUFFER_SIZE,sizeof(char));
 strcat(buffer,en_en_article[typ+3]);
 strcat(buffer,getNumberAsString(num));
 return buffer;
}
