#include "de.h"
#include "../Language.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char defAdjectiveEndings[16][4]={
 "e " ,"e " ,"e " ,"en ",
 "en ","e " ,"e " ,"en ",
 "en ","en ","en ","en ",
 "en ","en ","en ","en "
};
char indefAdjectiveEndings[16][4]={
 "er ","e " ,"es ","en ",
 "en ","e " ,"es ","en ",
 "en ","en ","en ","en ",
 "en ","en ","en ","en "
};
char* de::getAdjective(int adjective,int noun,bool plural, int atyp, int cas){
 char typ = getNounType(noun);
 FILE* rFile = fopen( DICTIONARY DE_FOLDER "adjectives","r");
 char* buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
 char* buffer2 = (char*)calloc(BUFFER_SIZE, sizeof(char));
 gotoline(rFile,adjective);
 fgets(buffer2,BUFFER_SIZE-1,rFile);
 fclose(rFile);
 int a=0;
 if (typ=='f') a=1;
 else if (typ=='n') a=2;
 if (plural) a=3;
 a+=cas*4;
 char* ending;
 if(atyp==-1)
 {
  ending=&defAdjectiveEndings[a][0];
 } else {
  ending=&indefAdjectiveEndings[a][0];
 }
 int u=0;
 int i=0;
 while(u==0){
  if (buffer[i]=='\n') u=1;
  i++;
 }
 buffer[i-1]=0;
 strcat(buffer,(const char*)buffer2+2*(sizeof(char)));
 if (noun>0 && buffer2[0]=='0') strcat(buffer,ending);
 else if (buffer2[0]!='1') strcat(buffer," ");
 return buffer;
}
