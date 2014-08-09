#include "en/en.h"
#include "de/de.h"
#include "Language.h"
#include "parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Language* getLanguageFromStringId(char* Id){
 Language* ret;
 if (!strcmp(Id,"en")){
  ret = new en_en;
 }
 else if (!strcmp(Id,"de")){
  ret = new de;
 }
 else exit(-1);
 return ret;
}
int main(int argc, char *argv[])
{
 if (argc!=3){
  printf("Usage: %s <language> <string-to-parse>\n",argv[0]);
  return -1;
 }
 Parser* out;
 out = new Parser;
 printf("%s\n",out->parse(argv[1],argv[2]));
 return 0;
}
